#ifndef INCLUDE_UNBAGGER_IMPLEMENTATION
#error Never include this file directly include 'unbagger.hpp'
#endif

#include <sensor_msgs/PointCloud2.h>
#include <rosbag/view.h>
#include "logger.hpp"


ros::Time drm::unbagger_internal::timestamp_t_to_ros_time(const drm::types::timestamp_t& timestamp) {
	using timestamp_seconds_t = std::chrono::duration<std::uint32_t>;

	return ros::Time{//Cast: timestamp_t -> ros::Time
		static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(timestamp).count()),
		static_cast<uint32_t>((timestamp - std::chrono::duration_cast<timestamp_seconds_t>(timestamp))
			.count())
	};
}

drm::types::timestamp_t drm::unbagger_internal::ros_time_to_timestamp_t(const ros::Time& timestamp) {
	using drm::types::timestamp_t;
	using second_timestamp_t = std::chrono::duration<timestamp_t::rep>;

	return timestamp_t{
		timestamp_t(timestamp.nsec) +
			std::chrono::duration_cast<timestamp_t>(second_timestamp_t(timestamp.sec))
	};
}

namespace drm::unbagger_internal {

#pragma pack(push, 1)
struct std_format_points_t {
	float x, y, z;
	float intensity;
	uint16_t ring;
	float time;
};
#pragma pack(pop)

}// namespace unbagger_internal

namespace drm {

template<typename F>
std::error_code unbagger::extract_lidar_scan_if(
	tcb::span<const std::string> lidar_topics,
	std::vector<types::lidar_scan_t>& lidar_scans,
	types::timestamp_t min_time,
	types::timestamp_t max_time,
	F&& predicate
) {
	using ec = drm::unbagger_error::codes;
	auto error_code = drm::unbagger_error::codes{};
	const auto min_time_total = min_time + m_bag_starting_time;
	const auto max_time_total = max_time + m_bag_starting_time;

	ros::Time min_time_ros = unbagger_internal::timestamp_t_to_ros_time(min_time_total);
	ros::Time max_time_ros = unbagger_internal::timestamp_t_to_ros_time(max_time_total);

	lidar_scans.clear();


	try {
		for (const auto& topic : lidar_topics) {
			auto view = rosbag::View(
				m_bag, rosbag::TopicQuery(topic), min_time_ros, max_time_ros
			);
			if (view.size() == 0) {
				continue;
			}
			/* First element is used to determine the name of the lidar sensor and the structure of the
			 * Pointcloud2-Format (e.g. Fields, Offset, etc.)
			 * It's assumed that all the messages in this topic are the same in this regard.
			 */
			const auto& first_elem = view.begin()->instantiate<sensor_msgs::PointCloud2>();

			const auto& name = first_elem->header.frame_id;
			const auto static_transform_it = m_static_transforms.find(name);
			if (static_transform_it == m_static_transforms.end()) {
				logger::warn(
					"No static transform for the frame_id % from the topic % found. Topic skipped.", name, topic
				);
				error_code = ec::no_static_tf_found;
				continue;
			}
			const auto static_transform = static_transform_it->second;

			auto timed_points = std::vector<types::timed_point_t>{};
			timed_points.reserve(view.size() * first_elem->width);

			constexpr auto standard_fields = std::string_view{
				"x,7,0,y,7,4,z,7,8,intensity,7,12,ring,4,16,time,7,18,"
			};

			auto all_fields = std::string();
			all_fields.reserve(standard_fields.size());
			for (const auto& field : first_elem->fields) {
				all_fields += field.name;
				all_fields += ',';
				all_fields += std::to_string(field.datatype);
				all_fields += ',';
				all_fields += std::to_string(field.offset);
				all_fields += ',';
			}

			if (standard_fields == all_fields) {
				for (const auto& msg : view) {
					const auto& elem = msg.instantiate<sensor_msgs::PointCloud2>();
					const auto& data = elem->data;
					const auto& frame_timestamp = unbagger_internal::ros_time_to_timestamp_t(elem->header.stamp);
					const auto raw_points = reinterpret_cast<const unbagger_internal::std_format_points_t*>(data
						.data());

					assert(elem->width == data.size() / sizeof(unbagger_internal::std_format_points_t));

					for (std::size_t i = 0; i < elem->width; i++) {
						const auto& raw_point = raw_points[i];
						const auto position = Eigen::Vector3d{ raw_point.x, raw_point.y, raw_point.z };

						if (predicate(position)) {

							using signed_timestamp_t = std::chrono::duration<
								std::make_signed_t<types::timestamp_t::rep>,
								types::timestamp_t::period
							>;

							const auto timestamp = std::chrono::duration_cast<types::timestamp_t>(
								frame_timestamp + std::chrono::duration_cast<signed_timestamp_t>(
									std::chrono::duration<double>(raw_point.time)
								)
							);

							const auto reverse_dst = std::find_if(
								timed_points.rbegin(),
								timed_points.rend(),
								[&timestamp](const auto& other_point) {
									return timestamp >= other_point.timestamp;
								}
							);

							timed_points.emplace(reverse_dst.base(), position, timestamp);
						}
					}

				}
			} else {
				//not implemented yet
				logger::warn(
					"The topic %s Field Format is wrong: Given %, Expected %. Topic skipped.",
					topic, all_fields, standard_fields
				);
				error_code = ec::wrong_field_format;
				continue;
			}
			timed_points.shrink_to_fit();

			lidar_scans.emplace_back(name, static_transform, timed_points);
		}

	} catch (const std::exception& e) {
		logger::warn("Error % in unbagger.ipp extract_lidar_scan_if", e.what());
		return make_error_code(ec::view_exception); //open view error code
	} catch (...) {
		return make_error_code(ec::view_unexpected_throw); //Something thrown that isn't a std::exception
	}


	return make_error_code(error_code);
}

}// namespace drm







const char* drm::unbagger_error::category::name() const noexcept {
	return "unbagger";
}


std::string drm::unbagger_error::category::message(int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::bag_open_exception:
		return "An exception was thrown while opening a rosbag. Look at the output to learn more.";
	case codes::bag_open_unexpected_throw:
		return "Something that isn't an exception was thrown while opening a rosbag.";
	case codes::view_exception:
		return "An exception was thrown while opening or using a view. Look at the output to learn more.";
	case codes::view_unexpected_throw:
		return "Something that isn't an exception was thrown while opening or using a view.";
	case codes::wrong_field_format:
		return "The Field Format in your PointCloud2 topic is not supported yet. Look at the output to learn more.";
	case codes::no_static_tf_found:
		return "There was no static transformation for the given frame_id or origin name. Look at the output to learn more.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_category& drm::unbagger_error_category() {
	static unbagger_error::category category;
	return category;
}

std::error_code drm::unbagger_error::make_error_code(codes e) {
	return { static_cast<int>(e), unbagger_error_category() };
}

