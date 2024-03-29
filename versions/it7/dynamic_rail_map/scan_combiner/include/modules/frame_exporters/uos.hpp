#pragma once

#include "config/types.hpp"

#include <cinttypes>
#include <filesystem>
#include <mutex>
#include <string_view>
#include <system_error>

namespace drm::frame_exporters {

struct uos {

	static constexpr std::string_view format_name = "uos";
	static constexpr std::string_view frame_folder_name = "frames";

	/**
	 * @brief Writes the given pose to "frames/scan<frame_index>.pose" and points to "frames/scan<frame_index>.3d".
	 *
	 * This function writes the pose transformation and points to separate files within the specified directory.
	 * The pose is written to a file named "scan<frame_index>.pose", and the points are written
	 * to a file named "scan<frame_index>.3d". Both files are created within the "frames" subdirectory
	 * of the provided chunk directory. The function ensures thread safety by unlocking the chunk lock
	 * before writing the files.
	 *
	 * @param chunk_directory The directory to be written in.
	 * @param chunk_lock      A mutex locking access to the chunk directory for other threads
	 * @param frame_index     The index of the given frame data.
	 * @param pose            The sensor transformation.
	 * @param points          The points in sensor space.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code write(
		const std::filesystem::path& chunk_directory,
		std::mutex& chunk_lock,
		std::size_t frame_index,
		const drm::types::transform_t& pose,
		tcb::span<const types::translation_t> points
	) noexcept;

private:
	/**
	 * @brief Creates a base filename for a given directory and frame index.
	 *
	 * The created base filename lays in "directory/frames" and is named
	 * "scan<frame_index>" where the @c frame_index is padded with up to 3 zeros.
	 *
	 * @param directory   The directory path where the file will be located.
	 * @param frame_index The index of the frame for which the filename is generated.
	 *
	 * @return An @c std::filesystem::path representing the constructed base filename.
	 */
	[[nodiscard]] static std::filesystem::path create_base_filename(
		const std::filesystem::path& directory, std::size_t frame_index
	) noexcept;

	/**
	 * @brief Writes the given sensor transformation to "<base_filename>.pose".
	 *
	 * The transformation is written out as { x, y, z, rotX, rotY, rotZ },
	 * where the rotations are the transforms euler-angles in degrees.
	 * The numbers are written in ASCII using the @c std::hexfloat format
	 * and separated by space characters.
	 *
	 * @param base_filename The base filename of the file to be written to.
	 * @param pose          The sensor transformation to be written to the file.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code write_pose(
		const std::filesystem::path& base_filename, const drm::types::transform_t& pose
	) noexcept;

	/**
	 * @brief Writes the given sensor transformation to "<base_filename>.3d".
	 *
	 * The points are written out in order x, y, z.
	 * The numbers are written in ASCII using the @c std::hexfloat format,
	 * separating components by spaces and points by line breaks.
	 *
	 * @param base_filename The base filename of the file to be written to.
	 * @param points        The points to be written to the file.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code write_points(
		const std::filesystem::path& base_filename, tcb::span<const types::translation_t> points
	) noexcept;
};

} // namespace drm::frame_exporters
