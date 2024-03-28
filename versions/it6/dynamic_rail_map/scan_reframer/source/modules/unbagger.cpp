#include "modules/unbagger.hpp"

#include "helpers/transform_conversion.hpp"

#include <exception>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <tf2_msgs/TFMessage.h>

namespace drm {

std::error_code drm::unbagger::open(const std::filesystem::path& bag_path) noexcept {
	using drm::types::timestamp_t;
	using drm::unbagger_error::make_error_code;
	using ec = drm::unbagger_error::codes;
	auto error = std::error_code{};

	if ((error = m_bag.open(bag_path))) {
		return error;
	}

	{
		auto full_view = rosbag::View{};
		if ((error = m_bag.get_view(full_view))) {
			return error;
		}

		m_bag_begin_time = ros_time_to_timestamp_t(full_view.getBeginTime());
		m_bag_end_time = ros_time_to_timestamp_t(full_view.getEndTime());
	}

	{
		auto static_transforms_view = rosbag::View{};
		if ((error = m_bag.get_topic_view(static_transforms_view, "/tf_static"))) {
			return error;
		}

		if (static_transforms_view.size() == 0) {
			return make_error_code(ec::empty_static_transform_message);
		}

		auto static_transform_msgs = boost::shared_ptr<tf2_msgs::TFMessage>{};
		if ((error = safe_rosbag::instantiate_msg_iterator<tf2_msgs::TFMessage>(
				 static_transforms_view.begin(),
				 static_transform_msgs
			 ))) {
			return error;
		}

		const auto& transforms = static_transform_msgs->transforms;

		m_static_transforms.clear();
		for (const auto& [header, name, transform] : transforms) {
			const auto& [translation, rotation] = transform;
			m_static_transforms.insert_or_assign(name, transform_from(translation, rotation));
		}
	}

	return error;
}

types::timestamp_t drm::unbagger::begin_tim() const noexcept {
	return m_bag_begin_time;
}

types::timestamp_t drm::unbagger::end_tim() const noexcept {
	return m_bag_end_time;
}

std::error_code drm::unbagger::extract_transforms(
	std::vector<types::timed_transform_t>& transforms,
	const std::string& transform_topic,
	const std::string& origin_name,
	const drm::types::timestamp_t min_time,
	const drm::types::timestamp_t max_time,
	const double max_position_deviation
) noexcept {
	using drm::unbagger_error::make_error_code;
	using ec = drm::unbagger_error::codes;
	auto error = std::error_code{};

	const auto static_transform_it = m_static_transforms.find(origin_name);
	if (static_transform_it == m_static_transforms.end()) {
		return make_error_code(ec::no_matching_static_transform);
	}

	const auto& [origin_to_world_translation, origin_to_world_rotation] = static_transform_it->second;
	const auto world_to_origin_space = matrix_from(origin_to_world_translation, origin_to_world_rotation).inverse();

	const auto [min_time_ros, max_time_ros] = get_absolute_ros_interval(min_time, max_time);

	auto transforms_view = rosbag::View{};
	if ((error = m_bag.get_topic_interval_view(transforms_view, transform_topic, min_time_ros, max_time_ros))) {
		return error;
	}

	transforms.resize(transforms_view.size());

	auto num_transforms = std::size_t{};

	using component_limit = std::numeric_limits<double>;
	static const auto invalid_position = types::translation_t{ component_limit::max(),
		                                                       component_limit::max(),
		                                                       component_limit::max() };
	auto prev_position = invalid_position;

	const auto max_position_deviation_sq = std::pow(max_position_deviation, 2.0);

	for (const auto& msg : transforms_view) {
		auto transform_msgs = boost::shared_ptr<tf2_msgs::TFMessage>{};
		if ((error = safe_rosbag::instantiate_msg<tf2_msgs::TFMessage>(msg, transform_msgs))) {
			logger::warn("Error while instantiating transform message: %", error.message());
			logger::warn("Skipping transform message.");
			continue;
		}

		if (transform_msgs->transforms.empty()) {
			logger::warn("No transforms in transform message");
			logger::warn("Skipping transform message.");
			continue;
		}

		const auto& first_transform = transform_msgs->transforms.front();
		const auto& [translation_ros, rotation_ros] = first_transform.transform;

		const auto tram_to_world_space = matrix_from(translation_ros, rotation_ros);
		const auto pose = transform_from(world_to_origin_space * tram_to_world_space);

		if (prev_position != invalid_position) {
			const auto dist_to_prev_sq = (prev_position - pose.translation).squaredNorm();
			if (dist_to_prev_sq < component_limit::epsilon()) {
				continue;
			} else if (dist_to_prev_sq > max_position_deviation_sq) {
				logger::warn(
					"Transform with coordinates (%m, %m, %m) was ignored because the distance to the previous "
					"transform (%m, %m, %m) was %m which exceeded the limit of %m.",
					pose.translation.x(),
					pose.translation.y(),
					pose.translation.z(),
					prev_position.x(),
					prev_position.y(),
					prev_position.z(),
					std::sqrt(dist_to_prev_sq),
					max_position_deviation
				);
				continue;
			}
		}

		prev_position = pose.translation;

		transforms[num_transforms++] = { transform_from(world_to_origin_space * tram_to_world_space),
			                             ros_time_to_timestamp_t(first_transform.header.stamp) };
	}

	transforms.resize(num_transforms);

	if (num_transforms != transforms_view.size()) {
		logger::warn(
			"Skipped % out of % transforms messages.",
			transforms_view.size() - num_transforms,
			transforms_view.size()
		);
	}

	return {};
}

std::error_code drm::unbagger::extract_velocities(
	std::vector<types::timed_velocity_t>& velocities,
	const std::string& odom_topic,
	const drm::types::timestamp_t min_time,
	const drm::types::timestamp_t max_time
) noexcept {
	using drm::unbagger_error::make_error_code;
	auto error = std::error_code{};

	const auto [min_time_ros, max_time_ros] = get_absolute_ros_interval(min_time, max_time);

	auto odom_view = rosbag::View{};
	if ((error = m_bag.get_topic_interval_view(odom_view, odom_topic, min_time_ros, max_time_ros))) {
		return error;
	}

	velocities.resize(odom_view.size());

	// Set previous velocity to impossible value
	constexpr auto double_max = std::numeric_limits<double>::max();
	auto prev_velocity = types::translation_t{ double_max, double_max, double_max };

	auto num_velocities = std::size_t{};
	for (const auto& msg : odom_view) {
		auto odom_msg = boost::shared_ptr<nav_msgs::Odometry>{};
		if ((error = safe_rosbag::instantiate_msg<nav_msgs::Odometry>(msg, odom_msg))) {
			logger::warn("Error while instantiating odometer message: %", error.message());
			logger::warn("Skipping transform message.");
			continue;
		}

		const auto& [x, y, z] = odom_msg->twist.twist.linear;
		const auto velocity = types::translation_t{ x, y, z };

		// Filter out duplicate messages.
		if (velocity == prev_velocity) {
			continue;
		}

		velocities[num_velocities++] = { velocity.norm(), ros_time_to_timestamp_t(odom_msg->header.stamp) };

		prev_velocity = velocity;
	}

	// Shrink vector to size without duplicates
	velocities.resize(num_velocities);

	if (num_velocities != odom_view.size()) {
		logger::warn("Skipped % out of % odometer messages.", odom_view.size() - num_velocities, odom_view.size());
	}

	return {};
}

std::error_code drm::unbagger::extract_imu_data(
	std::vector<types::timed_rotation_t>& rotations,
	const std::string& imu_topic,
	const drm::types::timestamp_t min_time,
	const drm::types::timestamp_t max_time
) noexcept {
	using drm::unbagger_error::make_error_code;
	auto error = std::error_code{};

	const auto [min_time_ros, max_time_ros] = get_absolute_ros_interval(min_time, max_time);

	auto imu_view = rosbag::View{};
	if ((error = m_bag.get_topic_interval_view(imu_view, imu_topic, min_time_ros, max_time_ros))) {
		return error;
	}

	rotations.resize(imu_view.size());

	// Set previous rotation to impossible value
	constexpr auto double_max = std::numeric_limits<double>::max();
	auto prev_rotation = types::rotation_t{ double_max, double_max, double_max, double_max };

	auto num_rotations = std::size_t{};
	for (const auto& msg : imu_view) {
		auto imu_msg = boost::shared_ptr<sensor_msgs::Imu>{};
		if ((error = safe_rosbag::instantiate_msg<sensor_msgs::Imu>(msg, imu_msg))) {
			logger::warn("Error while instantiating imu message: %", error.message());
			logger::warn("Skipping transform message.");
			continue;
		}

		const auto& [x, y, z, w] = imu_msg->orientation;
		const auto rotation = types::rotation_t{ w, x, y, z };

		// Filter out duplicate messages.
		if (rotation.w() == prev_rotation.w() and rotation.x() == prev_rotation.x() and
		    rotation.y() == prev_rotation.y() and rotation.z() == prev_rotation.z()) {
			continue;
		}

		rotations[num_rotations++] = { rotation, ros_time_to_timestamp_t(imu_msg->header.stamp) };

		prev_rotation = rotation;
	}

	// Shrink vector to size without duplicates
	rotations.resize(num_rotations);

	if (num_rotations != imu_view.size()) {
		logger::warn("Skipped % out of % imu messages.", imu_view.size() - num_rotations, imu_view.size());
	}

	return {};
}

} // namespace drm
