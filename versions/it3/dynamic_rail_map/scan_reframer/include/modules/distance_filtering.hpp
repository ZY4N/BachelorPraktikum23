#pragma once

namespace drm::distance_filtering {
/**
 * @brief Creates a distance-based filter for 3D points with the given maximum distance.
 *
 * This function generates a lambda which captures the given maximum distance and
 * returns true if the point is within the specified maximum distance, and false otherwise.
 *
 * @param max_distance The maximum allowed distance for 3D points.
 * @return The generated lambda.
 */
[[nodiscard]] inline auto create_simple_filter(double max_distance) noexcept;

/**
 * @brief Creates a filter for 3D points based on both radial and peripheral distances.
 *
 * This function generates a lambda which captures the given maximum radial and peripheral distances.
 * It returns true if the point is both within the specified radial and peripheral maximum distances,
 * and false otherwise.
 *
 * @param max_radial_distance     The maximum allowed radial distance for 3D points.
 * @param max_peripheral_distance The maximum allowed peripheral distance for 3D points.
 * @return The generated lambda.
 */
[[nodiscard]] inline auto create_peripheral_filter(double max_radial_distance, double max_peripheral_distance) noexcept;

} // namespace drm::distance_filtering

#define INCLUDE_DISTANCE_FILTERING_IMPLEMENTATION
#include "modules/distance_filtering.ipp"

#undef INCLUDE_DISTANCE_FILTERING_IMPLEMENTATION
