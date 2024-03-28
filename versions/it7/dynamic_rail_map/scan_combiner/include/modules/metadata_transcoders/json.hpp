#pragma once

#include "components/metadata.hpp"

#include <filesystem>
#include <system_error>

namespace drm::metadata_transcoders {

struct json {

	static constexpr std::string_view format_name = "json";

	/**
	 * @brief Checks if "directory/meta.json" exists.
	 *
	 * @param directory The directory path where the metadata is expected to be located.
	 *
	 * @return True if the directory contains metadata, false otherwise.
	 */
	[[nodiscard]] static bool contains_metadata(const std::filesystem::path& directory) noexcept;

	/**
	 * @brief Writes the given metadata to "directory/meta.json".
	 *
	 * @param directory The directory path the metadata is written to.
	 * @param meta      The metadata to be written.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code write(
		const std::filesystem::path& directory, const metadata::metadata_t& meta
	) noexcept;

	/**
	 * @brief Reads metadata from "directory/meta.json" to the given metadata reference.
	 *
	 * @param directory The directory path the metadata is written to.
	 * @param meta      Metadata reference to be writen to.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] static std::error_code read(
		const std::filesystem::path& directory, metadata::metadata_t& meta
	) noexcept;

private:
	static constexpr std::string_view filename = "meta.json";
};

namespace json_error {

enum class codes {
	ok = 0,
	wrong_type_json,
	member_does_not_exist_json
};

struct category : std::error_category {
	[[nodiscard]] const char* name() const noexcept override;
	[[nodiscard]] std::string message(int ev) const override;
};

[[nodiscard]] std::error_code make_error_code(codes e) noexcept;

} // namespace json_error

[[nodiscard]] inline std::error_category& json_error_category() noexcept;

} // namespace drm::metadata_transcoders

template<>
struct std::is_error_code_enum<drm::metadata_transcoders::json_error::codes> : public std::true_type {};
