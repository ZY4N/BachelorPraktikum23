#include "unbagger.hpp"
#include "transform_conversion.hpp"
#include <exception>
#include <tf2_msgs/TFMessage.h>
#include <nav_msgs/Odometry.h>


using ec = drm::unbagger_error::codes;

std::error_code drm::unbagger::open(const std::filesystem::path& bag_path) {
	using drm::types::timestamp_t;

	try {
		m_bag.open(bag_path, rosbag::bagmode::Read);
	} catch (const std::exception& e) {
		logger::warn("Error % in unbagger.cpp open", e.what());
		return make_error_code(ec::bag_open_exception);
	} catch (...) {
		return make_error_code(ec::bag_open_unexpected_throw);
	}

	try {
		rosbag::View view{ m_bag };
		const auto ros_begin_time = view.getBeginTime();

		m_bag_starting_time = unbagger_internal::ros_time_to_timestamp_t(ros_begin_time);//Cast ros::Time -> timestamp_t


	} catch (const std::exception& e) {
		logger::warn("Error % in unbagger.cpp open", e.what());
		return make_error_code(ec::view_exception);
	} catch (...) {
		return make_error_code(ec::view_unexpected_throw);
	}

	try {
		rosbag::View view{ m_bag, rosbag::TopicQuery("/tf_static") };

		assert(view.size() > 0);

		const auto static_transforms = view.begin();
		const auto& transform_msgs = static_transforms->instantiate<tf2_msgs::TFMessage>();
		const auto& transforms = transform_msgs->transforms;
		m_static_transforms.clear();

		for (const auto& [header, name, transform] : transforms) {
			const auto& [translation, rotation] = transform;

			m_static_transforms.insert_or_assign(
				name,
				types::transform_t{
					{ translation.x, translation.y, translation.z },
					{ rotation.w, rotation.x, rotation.y, rotation.z }
				}
			);
		}

	} catch (const std::exception& e) {
		logger::warn("Error % in unbagger.cpp open", e.what());
		return make_error_code(ec::view_exception);
	} catch (...) {
		return make_error_code(ec::view_unexpected_throw);
	}


	return {};
}

std::error_code drm::unbagger::extract_transforms(
	std::vector<types::timed_transform_t>& transforms,
	const std::string& transform_topic,
	const std::string& origin_name,
	drm::types::timestamp_t min_time,
	drm::types::timestamp_t max_time
) {
	const auto min_time_total = min_time + m_bag_starting_time;
	const auto max_time_total = max_time + m_bag_starting_time;

	ros::Time min_time_ros = unbagger_internal::timestamp_t_to_ros_time(min_time_total);
	ros::Time max_time_ros = unbagger_internal::timestamp_t_to_ros_time(max_time_total);

	try {
		const auto static_transform_it = m_static_transforms.find(origin_name);
		if (static_transform_it == m_static_transforms.end()) {
			//
			logger::error("No static transform found to given origin name: %", origin_name);
			return make_error_code(ec::no_static_tf_found);
		}

		const auto& [origin_to_world_translation, origin_to_world_rotation] = static_transform_it->second;
		const auto world_to_origin_space = matrix_from(
			origin_to_world_translation,
			origin_to_world_rotation
		).inverse();


		auto view = rosbag::View(
			m_bag, rosbag::TopicQuery(transform_topic), min_time_ros, max_time_ros
		);

		transforms.resize(view.size());

		std::transform(
			view.begin(), view.end(), transforms.begin(),
			[&](const auto& msg) -> types::timed_transform_t {
				const auto tf_msg = msg.template instantiate<tf2_msgs::TFMessage>();
				const auto& first_transform = tf_msg->transforms.front();

				const auto& [translation_ros, rotation_ros] = first_transform.transform;

				const auto tram_to_world_space = matrix_from(translation_ros, rotation_ros);

				return {
					transform_from(world_to_origin_space * tram_to_world_space),
					unbagger_internal::ros_time_to_timestamp_t(first_transform.header.stamp)
				};
			}
		);
	} catch (const std::exception& e) {
		logger::error("Error % in unbagger.cpp extract_transforms", e.what());
		return make_error_code(ec::view_exception);
	} catch (...) {
		return make_error_code(ec::view_unexpected_throw);
	}

	return {};
}

std::error_code drm::unbagger::extract_velocities(
	std::vector<types::timed_velocity_t>& velocities,
	const std::string& odom_topic,
	drm::types::timestamp_t min_time,
	drm::types::timestamp_t max_time
) {
	const auto min_time_total = min_time + m_bag_starting_time;
	const auto max_time_total = max_time + m_bag_starting_time;

	ros::Time min_time_ros = unbagger_internal::timestamp_t_to_ros_time(min_time_total);
	ros::Time max_time_ros = unbagger_internal::timestamp_t_to_ros_time(max_time_total);

	try {
		auto view = rosbag::View(
			m_bag, rosbag::TopicQuery(odom_topic), min_time_ros, max_time_ros
		);

		velocities.resize(view.size());

		// Set previous velocity to impossible value
		constexpr auto double_max = std::numeric_limits<double>::max();
		auto prev_velocity = types::translation_t{ double_max, double_max, double_max };

		std::size_t output_index = 0;
		for (const auto& msg : view) {
			const auto& odom_msg = msg.template instantiate<nav_msgs::Odometry>();
			const auto& [x, y, z] = odom_msg->twist.twist.linear;
			const auto velocity = types::translation_t{ x, y, z };

			// Filter out duplicate messages.
			if (velocity == prev_velocity) {
				continue;
			}

			velocities[output_index++] = {
				velocity.norm(),
				unbagger_internal::ros_time_to_timestamp_t(odom_msg->header.stamp)
			};

			prev_velocity = velocity;
		}

		// Shrink vector to size without duplicates
		velocities.resize(output_index);

	} catch (const std::exception& e) {
		logger::error("Error % in unbagger.cpp extract_velocities", e.what());
		return make_error_code(ec::view_exception); //open view error code
	} catch (...) {
		return make_error_code(ec::view_unexpected_throw); //Something thrown that isn't a std::exception
	}
	return {};

}



