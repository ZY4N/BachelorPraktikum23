#pragma once

#include "span.hpp"
#include "types.hpp"

#include <cinttypes>
#include <filesystem>
#include <system_error>
#include <utility>

namespace drm {
//--------------[ declarations ]--------------//

namespace frame_exporter {
/**
 * @brief Exports scans to the uos file format.
 *
 * For each input frame, this function generates two files in the target directory.
 * The '.pose' file contains the position and rotation information from which the frame's points were scanned.
 * The '.3d' file stores all point positions relative to this pose.
 * Both files share the base name  'scan<X>', where <X> represents the zero padded frame index.
 *
 * @note All numbers are stored as @c std::hexfloat.
 * @note This function will create the complete destination path if necessary.
 *
 * @param directory path to a directory.
 * @param frames A span of frames with scanner attributes and associated points.
 * @param num_threads Number of threads
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] std::error_code write_frames_to_uos_files(
	const std::filesystem::path& directory,
	tcb::span<const types::lidar_frame_t> frames,
	int num_threads = 1
) noexcept;

/**
 * @brief Exports scans to the kitty file format.
 *
 * This function generates a points file for each input frame and a single pose file in the target directory.
 * The 'pose.txt' file contains a list of the position and rotation information from which the frame's points were
 * scanned. The '*.bin' files store all point positions relative to their pose.
 *
 * @note All points are stored as floats in binary.
 * @note All poses are stored as the first 12 entries of an 4x4 Spatial Transformation Matrix.
 * @note These numbers are writen as double in digits. //TODO
 * @note This function will create the complete destination path if necessary.
 *
 * @param directory path to a directory.
 * @param frames A span of frames with scanner attributes and associated points.
 * @param num_threads Number of threads
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] std::error_code write_frames_to_removert_files(
	const std::filesystem::path& directory,
	tcb::span<const types::lidar_frame_t> frames,
	std::size_t frame_id_offset = 0,
	int num_threads = 1
) noexcept;

/**
 * @brief Counts the number of frames in pose file in the given directory.
 *
 * This function count the number of lines in "pose.txt" in the given directory.
 *
 * @param directory path to a directory.
 * @return An @c std::size_t .
 */
[[nodiscard]] std::size_t get_number_of_prev_frames(
	const std::filesystem::path& directory
) noexcept;

} // namespace frame_exporter

namespace frame_exporter_internal {

[[nodiscard]] std::error_code write_frame_set_to_uos_file(
	const std::filesystem::path& filename, tcb::span<const types::lidar_frame_t> frames, std::size_t index
) noexcept;

[[nodiscard]] std::error_code write_single_frame_to_uos_file(
	const std::filesystem::path& filename, const types::lidar_frame_t& frames
) noexcept;

[[nodiscard]] std::error_code write_points_to_uos_file(
	const std::filesystem::path& filename, tcb::span<const types::timed_point_t> points
) noexcept;

[[nodiscard]] std::error_code write_pose_to_uos_file(
	const std::filesystem::path& filename, const types::transform_t& pose
) noexcept;

[[nodiscard]] std::error_code write_points_to_removert_file(
	const std::filesystem::path& base_filename, tcb::span<const types::timed_point_t> points
) noexcept;

[[nodiscard]] std::error_code write_pose_to_removert_file(
	std::ofstream& output, const drm::types::transform_t& pose
) noexcept;

} // namespace frame_exporter_internal

} // namespace drm
