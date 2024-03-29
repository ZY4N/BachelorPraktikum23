#pragma once

#include "config/types.hpp"
#include "util/unique_enum_type.hpp"

#include <filesystem>
#include <mutex>
#include <optional>
#include <string_view>
#include <system_error>

namespace drm::frame_exportation {

using frame_format = unique_enum_type<0>;

/**
 * @brief Invokes the frame exportation implementation for the given frame format.
 *
 * @param format          The frame format to export in.
 * @param chunk_directory The directory to be written in.
 * @param chunk_lock      A mutex locking access to the chunk directory for other threads
 * @param frame_index     The index of the given frame data.
 * @param pose            The sensor transformation.
 * @param points          The points in sensor space.
 *
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] inline std::error_code write(
	frame_format format,
	const std::filesystem::path& chunk_directory,
	std::mutex& chunk_lock,
	std::size_t frame_index,
	const drm::types::transform_t& pose,
	tcb::span<const types::translation_t> points
) noexcept;

/**
 * @brief Generates a lookup table mapping @c frame_format s to their corresponding names.
 *
 * @return An array of pairs containing frame formats and their corresponding names.
 */
[[nodiscard]] inline constexpr auto get_format_name_lookup();

/**
 * @brief Retrieves the frame format corresponding to the given name.
 *
 * @param name The name of the frame format to retrieve.
 *
 * @return An optional containing the frame format if found, or std::nullopt if not.
 */
[[nodiscard]] inline constexpr std::optional<frame_format> get_format_by_name(std::string_view name);

/**
 * @brief Retrieves the name of the given @c frame_format.
 *
 * This function searches the format name lookup table for the given frame format and returns
 * its corresponding name if found.
 *
 * @param format The frame format for which to retrieve the name.
 *
 * @return An optional containing the name of the frame format if found, or std::nullopt if not.
 */
[[nodiscard]] inline constexpr std::optional<std::string_view> get_format_name(frame_format format);

} // namespace drm::frame_exportation

#define INCLUDE_FRAME_EXPORTATION_IMPLEMENTATION
#include "module_interfaces/frame_exportation.ipp"
#undef INCLUDE_FRAME_EXPORTATION_IMPLEMENTATION
