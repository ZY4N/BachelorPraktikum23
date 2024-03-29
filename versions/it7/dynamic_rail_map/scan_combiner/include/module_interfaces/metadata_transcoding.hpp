#pragma once

#include "components/metadata.hpp"
#include "util/unique_enum_type.hpp"

#include <filesystem>
#include <optional>
#include <string_view>
#include <system_error>

namespace drm::metadata_transcoding {

using metadata_format = unique_enum_type<1ul>;

/**
 * @brief Checks whether the given directory contains metadata of the specified format.
 *
 * @param format    The metadata format to check for.
 * @param directory The directory path where the metadata is expected to be located.
 *
 * @return true if the directory contains metadata of the specified format, false otherwise.
 */
[[nodiscard]] inline bool contains_metadata(metadata_format format, const std::filesystem::path& directory) noexcept;

/**
 * @brief Writes metadata to the specified format within the given directory.
 *
 * @param format    The metadata format to write.
 * @param directory The directory path the metadata is written to.
 * @param meta      The metadata to be written.
 *
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] inline std::error_code write(
	metadata_format format, const std::filesystem::path& directory, const metadata::metadata_t& meta
) noexcept;

/**
 * @brief Reads metadata in the specified format from the given directory.
 *
 * @param format    The metadata format to read.
 * @param directory The directory path where the metadata is expected to be located.
 * @param meta      A reference to the metadata struct to store the data in.
 *
 * @return An @c std::error_code indicating the status of the operation.
 */
[[nodiscard]] inline std::error_code read(
	metadata_format format, const std::filesystem::path& directory, metadata::metadata_t& meta
) noexcept;

/**
 * @brief Generates a lookup table mapping @c metadata_format s to their corresponding names.
 *
 * @return An array of pairs containing metadata formats and their corresponding names.
 */
[[nodiscard]] inline constexpr auto get_format_name_lookup();

/**
 * @brief Retrieves the metadata format corresponding to the given name.
 *
 * @param name The name of the metadata format to retrieve.
 *
 * @return An optional containing the metadata format if found, or std::nullopt if not.
 */
[[nodiscard]] inline constexpr std::optional<metadata_format> get_format_by_name(std::string_view name);

/**
 * @brief Retrieves the name of the given @c metadata_format.
 *
 * This function searches the metadata name lookup table for the given metadata format and returns
 * its corresponding name if found.
 *
 * @param format The metadata format for which to retrieve the name.
 *
 * @return An optional containing the name of the metadata format if found, or std::nullopt if not.
 */
[[nodiscard]] inline constexpr std::optional<std::string_view> get_format_name(metadata_format format);

} // namespace drm::metadata_transcoding

#define INCLUDE_METADATA_TRANSCODING_IMPLEMENTATION
#include "module_interfaces/metadata_transcoding.ipp"
#undef INCLUDE_METADATA_TRANSCODING_IMPLEMENTATION
