#pragma once

#include "helpers/safe_rosbag.hpp"
#include "span.hpp"
#include "types.hpp"

#include <filesystem>
#include <rosbag/bag.h>
#include <string>
#include <system_error>
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
	[[nodiscard]] std::error_code open(const std::filesystem::path& bag_path) noexcept;


	[[nodiscard]] types::timestamp_t begin_tim() const noexcept;

	[[nodiscard]] types::timestamp_t end_tim() const noexcept;

	/**
	 * @brief  Reads and filters lidar scans from given topics and time range.
	 *
	 * @note The earliest message in the rosbag has the time 0.
	 * @note Topic messages must be in the sensor_msg/PointCloud2 Format. And consist of certain fields.
	 *
	 * @tparam P Predicate type
	 * @param lidar_topics Range of ros topics.
	 * @param lidar_scans A vector in which the extracted lidar scans are stored.
	 * @param min_time The beginning of the time range.
	 * @param max_time The end of the time range.
	 * @param predicate Lambda to filter points based on there sensor space location.
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	template<typename F, typename P>
	[[nodiscard]] inline std::error_code extract_points_if(
		const std::string& lidar_topic,
		std::vector<types::timed_point_t>& lidar_points,
		types::transform_t& sensor_transform,
		types::timestamp_t min_time,
		types::timestamp_t max_time,
		const F& lidar_point_parser,
		const P& lidar_point_predicate
	) noexcept;

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
		drm::types::timestamp_t max_time,
		double max_position_deviation
	) noexcept;

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
	) noexcept;

	[[nodiscard]] std::error_code extract_imu_data(
		std::vector<types::timed_rotation_t>& rotations,
		const std::string& imu_topic,
		drm::types::timestamp_t min_time,
		drm::types::timestamp_t max_time
	) noexcept;

protected:
	[[nodiscard]] inline std::pair<ros::Time, ros::Time> get_absolute_ros_interval(
		drm::types::timestamp_t min_time, drm::types::timestamp_t max_time
	) noexcept;

private:
	safe_rosbag m_bag;
	types::timestamp_t m_bag_begin_time, m_bag_end_time;
	std::unordered_map<std::string, types::transform_t> m_static_transforms;
};

namespace unbagger_error {

enum class codes {
	ok = 0,
	empty_static_transform_message,
	empty_lidar_frames_view,
	no_matching_static_transform
};

struct category : std::error_category {
	[[nodiscard]] inline const char* name() const noexcept override;

	[[nodiscard]] inline std::string message(int ev) const override;
};

[[nodiscard]] inline std::error_code make_error_code(codes e) noexcept;

} // namespace unbagger_error

[[nodiscard]] inline std::error_category& unbagger_error_category() noexcept;

} // namespace drm

template<>
struct std::is_error_code_enum<drm::unbagger_error::codes> : public std::true_type {};

#define INCLUDE_UNBAGGER_IMPLEMENTATION
#include "modules/unbagger.ipp"
#undef INCLUDE_UNBAGGER_IMPLEMENTATION
