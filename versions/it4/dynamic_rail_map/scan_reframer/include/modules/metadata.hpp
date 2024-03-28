#pragma once

#include "types.hpp"
#include "version.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace drm {

namespace metadata {

struct version_t {
	const unsigned major, minor, revision;

	bool operator==(const version_t& rhs) const;
	bool operator!=(const version_t& rhs) const;
};

struct reframer_settings_t {
	const std::vector<std::string> lidar_topics_vector;
	const types::timestamp_t relative_begin_time;
	const types::timestamp_t relative_end_time;
	const double max_position_deviation;
	const double max_scan_position_deviation;
	const unsigned int max_radial_distance;
	const unsigned int max_peripheral_distance;

	bool operator==(const reframer_settings_t& rhs) const;
	bool operator!=(const reframer_settings_t& rhs) const;
};

struct reframer_config_t {
	const version_t version;
	const reframer_settings_t settings;

	bool operator==(const reframer_config_t& rhs) const;
	bool operator!=(const reframer_config_t& rhs) const;
};

struct date_t {
	int day, month, year;

	bool operator==(const date_t& rhs) const;
	bool operator!=(const date_t& rhs) const;
};

struct scan_t {
	const long reframer_settings_index, reframer_config_index;
	date_t date;
	std::vector<unsigned long> bins;

	bool operator==(const scan_t& rhs) const;
	bool operator!=(const scan_t& rhs) const;
};

struct metadata_t {
	std::vector<reframer_config_t> configs;
	std::vector<std::string> rosbags;
	std::vector<scan_t> scans;

	bool operator==(const metadata_t& rhs) const;
	bool operator!=(const metadata_t& rhs) const;
};

[[nodiscard]] version_t get_version() noexcept;

[[nodiscard]] date_t get_current_date();

[[nodiscard]] std::error_code create_meta_json(const std::filesystem::path& filename);

} // namespace metadata

namespace metadata_error {

enum class codes {
	ok = 0
};

struct category : std::error_category {
	[[nodiscard]] const char* name() const noexcept override;
	[[nodiscard]] std::string message(int ev) const override;
};

[[nodiscard]] std::error_code make_error_code(codes e) noexcept;

} // namespace metadata_error

[[nodiscard]] inline std::error_category& metadata_error_category() noexcept;

} // namespace drm

template<>
struct std::is_error_code_enum<drm::metadata_error::codes> : public std::true_type {};
