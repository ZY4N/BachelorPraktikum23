#pragma once

#include "types.hpp"

#include <rosbag/view.h>
#include <system_error>

namespace drm::lidar_parsers {

/**
 * @brief Reads and filters velodyne lidar sensor data from the given @c rosbag::View into the output vector.
 *
 * Before beginning to read, this function checks if the fields of the first @c PointCloud2 meet
 * the layout and type requirements. I the check fails it returns the corresponding @c std::error_code.
 * Otherwise it assumes that all following @c PointCloud2 messages are laid out equally and starts reading.
 * All points are filtered using the predicate, have timing information added and are then inserted into the output
 * vector. The output vector is sorted by timestamp in ascending order.
 *
 * @note                    The view must only contain @c PointCloud2 messages containing the required fields.
 *                          This includes fields 'x', 'y', 'z' and 'time' of type 'float32' with
 *                          the respective byte offsets 0, 4, 8 and 18.
 *
 * @tparam P                The type of the given point predicate.
 * @param lidar_frames_view The view containing the velodyne lidar sensor data.
 * @param timed_points      The output vector to be written to.
 * @param predicate         The predicate to filter the lidar points.
 *
 * @return                   An @c std::error_code indicating the status of the operation.
 */
template<typename P>
[[nodiscard]] inline std::error_code parse_velodyne_lidar_points(
	rosbag::View& lidar_frames_view, std::vector<types::timed_point_t>& timed_points, const P& predicate
) noexcept;

namespace velodyne_lidar_point_parsing_error {
enum class codes {
	ok = 0,
	point_field_mismatch
};

struct category : std::error_category {
	[[nodiscard]] inline const char* name() const noexcept override;

	[[nodiscard]] inline std::string message(int ev) const override;
};

[[nodiscard]] inline std::error_code make_error_code(codes e) noexcept;

} // namespace velodyne_lidar_point_parsing_error

} // namespace drm::lidar_parsers

[[nodiscard]] inline std::error_category& unbagger_error_category() noexcept;

template<>
struct std::is_error_code_enum<drm::lidar_parsers::velodyne_lidar_point_parsing_error::codes> : public std::true_type {
};

#define INCLUDE_UNBAGGER_IMPLEMENTATION
#include "lidar_parsers/parse_velodyne_lidar_points.ipp"
#undef INCLUDE_UNBAGGER_IMPLEMENTATION
