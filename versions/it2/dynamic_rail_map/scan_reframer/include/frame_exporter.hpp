#pragma once

#include <filesystem>
#include <system_error>
#include <cinttypes>
#include <utility>
#include "types.hpp"
#include "span.hpp"


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
 * @note This function will create the  destination directory if necessary.
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
);

} // namespace frame_exporter

namespace frame_exporter_internal {

[[nodiscard]] std::error_code write_frame_set_to_uos_file(
	const std::filesystem::path& filename,
	tcb::span<const types::lidar_frame_t> frames,
	std::size_t index
);

[[nodiscard]] std::error_code write_single_frame_to_uos_file(
	const std::filesystem::path& filename,
	const types::lidar_frame_t& frames
);

[[nodiscard]] std::error_code write_points_to_uos_file(
	const std::filesystem::path& filename,
	tcb::span<const types::timed_point_t> points
);

[[nodiscard]] std::error_code write_pose_to_uos_file(
	const std::filesystem::path& filename,
	const types::transform_t& pose
);

} // namespace frame_exporter_internal

} // namespace drm
