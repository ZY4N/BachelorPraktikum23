#pragma once

#include "span.hpp"
#include "types.hpp"

#include <cinttypes>
#include <filesystem>
#include <system_error>
#include <utility>

namespace drm {
//--------------[ declarations ]--------------//

namespace chunk_exporter {

/**
 * @brief Exports points as .bin files.
 *
 * @note All points are stored as floats in binary.
 *
 * @param directory path to a directory.
 * @param points A span of points
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] std::error_code write_points_to_removert_file(
	const std::filesystem::path& directory, tcb::span<const types::translation_t> points, std::size_t frame_index
) noexcept;

/**
 * @brief Exports poses as .txt file
 *
 * @note All poses are stored as the first 12 entries of an 4x4 Spatial Transformation Matrix.
 *
 * @param directory  path to a directory.
 * @param pose scanner attributes
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] std::error_code write_pose_to_removert_file(
	const std::filesystem::path& directory, const drm::types::transform_t& pose
) noexcept;

/**
 * @brief Counts the number of frames in pose file in the given directory.
 *
 * This function count the number of lines in "pose.txt" in the given directory.
 *
 * @param directory path to a directory.
 * @return An @c std::size_t .
 */
[[nodiscard]] std::size_t get_number_of_prev_frames(const std::filesystem::path& directory) noexcept;

} // namespace chunk_exporter

// namespace chunk_exporter_internal {
// } // namespace chunk_exporter_internal

} // namespace drm
