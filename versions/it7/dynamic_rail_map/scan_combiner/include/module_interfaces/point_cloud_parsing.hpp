#pragma once

#include "config/types.hpp"
#include "util/unique_enum_type.hpp"

#include <array>
#include <optional>
#include <rosbag/view.h>
#include <system_error>

namespace drm::point_cloud_parsing {

using sensor_type = unique_enum_type<2>;

/**
 * @brief Invokes the point cloud parser implementation for the given sensor type.
 *
 * @tparam P                The type of the given point predicate.
 * @param lidar_frames_view The view containing the sensor point data.
 * @param timed_points      The output vector to be written to.
 * @param predicate         The predicate to filter the points in sensor space.
 *
 * @return An @c std::error_code indicating the status of the operation.
 */
template<typename P>
[[nodiscard]] inline std::error_code parse(
	const sensor_type type,
	rosbag::View& lidar_frames_view,
	std::vector<types::timed_point_t>& timed_points,
	const P& predicate
) noexcept;

/**
 * @brief Generates a lookup table mapping @c sensor_type s to their corresponding names.
 *
 * @return An array of pairs containing sensor types and their corresponding names.
 */
[[nodiscard]] inline constexpr auto get_sensor_name_lookup();

/**
 * @brief Retrieves the sensor type corresponding to the given name.
 *
 * @param name The name of the sensor type to retrieve.
 *
 * @return An optional containing the sensor type if found, or std::nullopt if not.
 */
[[nodiscard]] inline constexpr std::optional<sensor_type> get_sensor_type_by_name(std::string_view name);

/**
 * @brief Retrieves the name of the given @c sensor_type.
 *
 * This function searches the sensor name lookup table for the given sensor type and returns
 * its corresponding name if found.
 *
 * @param type The sensor type for which to retrieve the name.
 *
 * @return An optional containing the name of the sensor type if found, or std::nullopt if not.
 */
[[nodiscard]] inline constexpr std::optional<std::string_view> get_sensor_name(sensor_type type);

} // namespace drm::point_cloud_parsing

#define INCLUDE_POINT_CLOUD_PARSING_IMPLEMENTATION
#include "module_interfaces/point_cloud_parsing.ipp"
#undef INCLUDE_POINT_CLOUD_PARSING_IMPLEMENTATION
