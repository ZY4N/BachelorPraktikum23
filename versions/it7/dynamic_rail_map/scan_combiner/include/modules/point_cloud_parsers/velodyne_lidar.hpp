#pragma once

#include "config/types.hpp"

#include <rosbag/view.h>
#include <string_view>
#include <system_error>

namespace drm::point_cloud_parsers {

struct velodyne_lidar {

	static constexpr std::string_view sensor_name = "velodyne_lidar";

	/**
	 * @brief Reads and filters velodyne LiDAR sensor data from the given @c rosbag::View into the output vector.
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
	 * @param lidar_frames_view The view containing the velodyne LiDAR sensor data.
	 * @param timed_points      The output vector to be written to.
	 * @param predicate         The predicate to filter the lidar points.
	 *
	 * @return                   An @c std::error_code indicating the status of the operation.
	 */
	template<typename P>
	[[nodiscard]] inline static std::error_code parse(
		rosbag::View& lidar_frames_view, std::vector<types::timed_point_t>& timed_points, const P& predicate
	) noexcept;
};

} // namespace drm::point_cloud_parsers

#define INCLUDE_VELODYNE_LIDAR_IMPLEMENTATION
#include "modules/point_cloud_parsers/velodyne_lidar.ipp"
#undef INCLUDE_VELODYNE_LIDAR_IMPLEMENTATION
