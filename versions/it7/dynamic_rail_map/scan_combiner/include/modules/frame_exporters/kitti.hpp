#pragma once

#include "config/types.hpp"

#include <cinttypes>
#include <filesystem>
#include <mutex>
#include <string_view>
#include <system_error>

namespace drm::frame_exporters {

struct kitti {

	static constexpr std::string_view format_name = "kitti";

	/**
	 * @brief Appends the given pose to "pose.txt" and writes the points to "<frame_index>.bin".
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

	// private: commented out for testing

	static constexpr std::string_view frame_folder_name = "frames";
	static constexpr std::string_view pose_filename = "pose.txt";

	/**
	 * @brief Appends poses to "directory/pose.txt".
	 *
	 * Stores the first 12 entries of the 4x4 sensor transformation matrix.
	 * The numbers are stored in ASCII with 16 digits per number,
	 * in one line separated by space characters.
	 *
	 * @note Will create a new file if "pose.txt" does not exist yet.
	 *
	 * @param directory Path to destination directory.
	 * @param pose      Sensor transformation.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code write_pose(
		const std::filesystem::path& directory, const drm::types::transform_t& pose
	) noexcept;

	/**
	 * @brief Writes given points into "directory/<frame_index>.bin".
	 *
	 * The points are stored in binary 32-bit floats in order { x, y, z, r },
	 * while the reflectance value @c r is always set to 1.0.
	 *
	 * @note The frame index is padded with up to 6 zeros.
	 *
	 * @param directory   Path to destination directory.
	 * @param points      Span of points to be written out.
	 * @param frame_index Frame index to be used for filename.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code write_points(
		const std::filesystem::path& directory, tcb::span<const types::translation_t> points, std::size_t frame_index
	) noexcept;
};

} // namespace drm::frame_exporters
