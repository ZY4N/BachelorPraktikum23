#pragma once

#include "types.hpp"

#include <ros/time.h>

namespace drm {

/**
 * @brief Convert a @c types::timestamp_t to the ROS Time representation.
 *
 * This function takes a @c types::timestamp_t and converts it to the ROS Time representation.
 * The resulting ROS Time is represented as the sum of seconds and nanoseconds since the
 * Unix epoch (1970-01-01 00:00:00 UTC).
 *
 * @note             It is crucial to note that the behavior of this function for timestamps beyond
 *                   ros::TIME_MAX (Unix time 4294967295999999999, 2106 06:28:16 UTC) is undefined.
 *
 * @param timestamp  The @c types::timestamp_t to be converted.
 *
 * @return           A ROS Time representation converted from the provided custom timestamp.
 */
[[nodiscard]] inline ros::Time timestamp_t_to_ros_time(const types::timestamp_t& timestamp) noexcept;

/**
 * @brief Convert a ROS Time representation to a @c types::timestamp_t.
 *
 * This function takes a ROS Time representation and converts it to a @c types::timestamp_t.
 * The ROS Time is expected to be represented as the sum of seconds and nanoseconds since
 * the Unix epoch (1970-01-01 00:00:00 UTC).
 *
 * @param timestamp  The ROS Time representation to be converted to a custom timestamp.
 *
 * @return           A @c types::timestamp_t converted from the provided ROS Time.
 */
[[nodiscard]] inline types::timestamp_t ros_time_to_timestamp_t(const ros::Time& timestamp) noexcept;

} // namespace drm

#define INCLUDE_ROS_TIME_CONVERSION_IMPLEMENTATION
#include "helpers/ros_time_conversion.ipp"
#undef INCLUDE_ROS_TIME_CONVERSION_IMPLEMENTATION
