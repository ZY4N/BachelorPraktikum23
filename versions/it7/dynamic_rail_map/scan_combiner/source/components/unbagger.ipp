#ifndef INCLUDE_UNBAGGER_IMPLEMENTATION
#	error Never include this file directly include 'unbagger.hpp'
#endif

#include "helpers/ros_time_conversion.hpp"
#include "util/logger.hpp"

#include <rosbag/view.h>
#include <sensor_msgs/PointCloud2.h>

namespace drm {

const char* unbagger_error::category::name() const noexcept {
	return "unbagger";
}

std::string unbagger_error::category::message(int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::empty_static_transform_message:
		return "Static transform message does not contain any transforms.";
	case codes::empty_lidar_frames_view:
		return "Tried opening empty lidar frame view.";
	case codes::no_matching_static_transform:
		return "There was no static transformation matching the given frame_id or origin name.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_category& unbagger_error_category() noexcept {
	static unbagger_error::category category;
	return category;
}

std::error_code unbagger_error::make_error_code(codes e) noexcept {
	return { static_cast<int>(e), unbagger_error_category() };
}

[[nodiscard]] std::pair<ros::Time, ros::Time> unbagger::get_absolute_ros_interval(
	drm::types::timestamp_t min_time, drm::types::timestamp_t max_time
) noexcept {
	const auto absolute_min_time = min_time + m_bag_begin_time;
	const auto absolute_max_time = max_time + m_bag_begin_time;

	return { timestamp_t_to_ros_time(absolute_min_time), timestamp_t_to_ros_time(absolute_max_time) };
}

template<typename P>
std::error_code unbagger::extract_points_if(
	const std::string& lidar_topic,
	const point_cloud_parsing::sensor_type sensor_type,
	std::vector<types::timed_point_t>& lidar_points,
	types::transform_t& sensor_transform,
	types::timestamp_t min_time,
	types::timestamp_t max_time,
	const P& lidar_point_predicate
) noexcept {
	using unbagger_error::make_error_code;
	using ec = unbagger_error::codes;
	auto error = std::error_code{};

	const auto [min_time_ros, max_time_ros] = get_absolute_ros_interval(min_time, max_time);

	auto lidar_frames_view = rosbag::View{};
	if ((error = m_bag.get_topic_interval_view(lidar_frames_view, lidar_topic, min_time_ros, max_time_ros))) {
		return error;
	}

	if (lidar_frames_view.size() == 0) {
		return make_error_code(ec::empty_lidar_frames_view);
	}

	auto first_lidar_frames = boost::shared_ptr<sensor_msgs::PointCloud2>{};
	if ((error = safe_rosbag::instantiate_msg_iterator<sensor_msgs::PointCloud2>(
			 lidar_frames_view.begin(),
			 first_lidar_frames
		 ))) {
		return error;
	}

	const auto sensor_transform_it = m_static_transforms.find(first_lidar_frames->header.frame_id);
	if (sensor_transform_it == m_static_transforms.end()) {
		return make_error_code(ec::no_matching_static_transform);
	}

	sensor_transform = sensor_transform_it->second;

	return point_cloud_parsing::parse<P>(sensor_type, lidar_frames_view, lidar_points, lidar_point_predicate);
}

} // namespace drm
