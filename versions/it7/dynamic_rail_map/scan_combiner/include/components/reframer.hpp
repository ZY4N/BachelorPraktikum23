#pragma once

#include "config/types.hpp"
#include "span.hpp"

#include <system_error>

namespace drm {

/**
 * @brief Namespace containing functions for reframing LiDAR scans.
 */
namespace reframer {

/**
 * @brief Reframes LiDAR scans so one frame consist of points that where scanned from within a given radius.
 *
 * This function utilizes Catmull-Rom splines to approximate the positions, rotations and velocities
 * of the LiDAR sensor for each point.
 * This information is then used to map each point to the destination space,
 * grouping the points into frames of points that where scanned from within the given radius.
 *
 * @note Only points with a timestamp in @c timed_transforms and @c timed_transforms are transformed.
 * @note The Catmull-Rom splines require an extra transform and velocity data point before and after the points.
 *
 * @param timed_points                    A by timestamp ascendingly sorted range of timed points to be remapped.
 * @param timed_transforms                A by timestamp ascendingly sorted range of timed tram to destination space
 * transforms.
 * @param timed_velocities                A by timestamp ascendingly sorted range of timed velocities.
 * @param sensor_to_vehicle_space         The transform from the sensor to the vehicle space.
 * @param max_sensor_position_deviation   The maximum distance in meters between scan positions in one frame.
 * @param frames                          The remapped transforms and corresponding point range.
 *
 * @return An @c std::error_code indicating possible reasons for points being omitted.
 */
[[nodiscard]] std::error_code reframe_to_closest_scan_positions(
	tcb::span<types::timed_point_t>& timed_points,
	tcb::span<const types::timed_transform_t> timed_transforms,
	tcb::span<const types::timed_velocity_t> timed_velocities,
	const types::transform_t& sensor_to_vehicle_space,
	double max_sensor_position_deviation,
	std::vector<types::lidar_frame_t>& frames
) noexcept;

} // namespace reframer

namespace reframer_internal {

template<typename T>
[[nodiscard]] double calculate_t(const T& p0, const T& p1) noexcept;

template<typename T>
[[nodiscard]] T eval_catmull_rom_spline(
	const T& p0, const T& p1, const T& p2, const T& p3, double dist_01, double dist_12, double dist_23, double t
) noexcept;

template<typename T>
[[nodiscard]] typename tcb::span<T>::reverse_iterator last_value_before_or_at(
	tcb::span<T> timed_values, types::timestamp_t timestamp
) noexcept;

template<typename T>
[[nodiscard]] typename tcb::span<T>::iterator first_value_after_or_at(
	tcb::span<T> timed_values, types::timestamp_t timestamp
) noexcept;

[[nodiscard]] double advance_and_sample_velocity(
	tcb::span<const types::timed_velocity_t>::iterator& velocity_it, const types::timestamp_t& timestamp
) noexcept;

[[nodiscard]] types::lidar_frame_t reframe_points_to_pose(
	tcb::span<types::timed_point_t> points, const types::transform_t& pose
) noexcept;

[[nodiscard]] std::pair<std::size_t, double> approximate_step_sizes(
	tcb::span<const drm::types::timed_transform_t>::iterator& transform_it,
	tcb::span<const drm::types::timed_velocity_t>::iterator& velocity_it,
	tcb::span<const drm::types::timed_point_t> points,
	std::vector<double>& steps
) noexcept;

} // namespace reframer_internal

namespace reframer_error {

enum class codes {
	ok = 0,
	not_enough_transforms,
	not_enough_velocities,
	time_ranges_not_overlapping,
	no_lidar_point_entry_point_found,
	no_transform_entry_point_found,
	no_velocity_entry_point_found
};

struct category : std::error_category {
	[[nodiscard]] const char* name() const noexcept override;
	[[nodiscard]] std::string message(int ev) const override;
};

[[nodiscard]] std::error_code make_error_code(codes e) noexcept;

} // namespace reframer_error

[[nodiscard]] inline std::error_category& reframer_error_category() noexcept;

} // namespace drm

template<>
struct std::is_error_code_enum<drm::reframer_error::codes> : public std::true_type {};
