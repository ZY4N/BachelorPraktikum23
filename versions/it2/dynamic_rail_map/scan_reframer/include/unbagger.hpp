#pragma once

#include "types.hpp"
#include <system_error>
#include <string>
#include "span.hpp"
#include <rosbag/bag.h>
#include <filesystem>
#include <vector>


namespace drm {

/**
 * @brief A class to open a rosbag and extract needed data from it.
 */
class unbagger {
public:
	/**
	 * @brief Opens the rosbag at the given path and reads the static_transformation and begin time.
	 * @param bag_path Path to rosbag.
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] std::error_code open(const std::filesystem::path& bag_path);

	/**
	 * @brief  Reads and filters lidar scans from given topics and time range.
	 *
	 * @note The earliest message in the rosbag has the time 0.
	 * @note Topic messages must be in the sensor_msg/PointCloud2 Format. And consist of certain fields.
	 *
	 * @tparam F Predicate type
	 * @param lidar_topics Range of ros topics.
	 * @param lidar_scans A vector in which the extracted lidar scans are stored.
	 * @param min_time The beginning of the time range.
	 * @param max_time The end of the time range.
	 * @param predicate Lambda to filter points based on there sensor space location.
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	template<typename F>
	[[nodiscard]] inline std::error_code extract_lidar_scan_if(
		tcb::span<const std::string> lidar_topics,
		std::vector<types::lidar_scan_t>& lidar_scans,
		types::timestamp_t min_time,
		types::timestamp_t max_time,
		F&& predicate
	);

	/**
	 * @brief Reads dynamic transforms from a given topic and time range
	 * 	and stores them in relation to a given origin.
	 *
	 * @note The earliest message in the rosbag has the time 0.
	 * @note Topic type must be @c tf2_msgs/TFMessage.
	 *
	 * @param transform_topic Topic with dynamic transforms.
	 * @param transforms A vector in which the extracted dynamic transforms are stored.
	 * @param origin_name The frame_id of the origin marker.
	 * @param min_time The beginning of the time range.
	 * @param max_time The end of the time range.
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] std::error_code extract_transforms(
		std::vector<types::timed_transform_t>& transforms,
		const std::string& transform_topic,
		const std::string& origin_name,
		drm::types::timestamp_t min_time,
		drm::types::timestamp_t max_time
	);

	/**
	 * @brief Reads linear velocity data from a given topic and time range
	 * 	and stores their norm with a timestamp in the given vector.
	 *
	 * @note The earliest message in the rosbag has the time 0.
	 * @note Topic type must be @c nav_msgs/Odometry.
	 *
	 * @param odom_topic Topic with odometer data.
	 * @param velocities A vector in which the extracted velocities are saved.
	 * @param min_time The beginning of the time range.
	 * @param max_time The end of the time range.
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] std::error_code extract_velocities(
		std::vector<types::timed_velocity_t>& velocities,
		const std::string& odom_topic,
		drm::types::timestamp_t min_time,
		drm::types::timestamp_t max_time
	);

private:
	rosbag::Bag m_bag;
	types::timestamp_t m_bag_starting_time;
	std::unordered_map<std::string, types::transform_t> m_static_transforms;
};
namespace unbagger_internal {

[[nodiscard]] inline ros::Time timestamp_t_to_ros_time(
	const drm::types::timestamp_t& timestamp
);

[[nodiscard]] inline drm::types::timestamp_t ros_time_to_timestamp_t(
	const ros::Time& timestamp
);

}// namespace unbagger_internal

namespace unbagger_error {

enum class codes {
	ok = 0,
	bag_open_exception,
	bag_open_unexpected_throw,
	view_exception,
	view_unexpected_throw,
	wrong_field_format,
	no_static_tf_found
};

struct category : std::error_category {
	[[nodiscard]] inline const char* name() const noexcept override;

	[[nodiscard]] inline std::string message(int ev) const override;
};

[[nodiscard]] inline std::error_code make_error_code(codes e);

} // namespace unbagger_error

[[nodiscard]] inline std::error_category& unbagger_error_category();

} // namespace drm

template<>
struct std::is_error_code_enum<drm::unbagger_error::codes> : public std::true_type {};

#define INCLUDE_UNBAGGER_IMPLEMENTATION
#include "unbagger.ipp"


#undef INCLUDE_UNBAGGER_IMPLEMENTATION
