#pragma once

#include "types.hpp"
#include "version.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace drm {

namespace metadata {

struct version_t {
	const unsigned major, minor, revision;

	bool operator==(const version_t& rhs) const;
	bool operator!=(const version_t& rhs) const;
};

struct reframer_parameters_t {
	const std::vector<std::string> lidar_topics_vector;
	const types::timestamp_t relative_begin_time;
	const types::timestamp_t relative_end_time;
	const double max_position_deviation;
	const double max_scan_position_deviation;
	const double max_radial_distance;
	const double max_peripheral_distance;

	bool operator==(const reframer_parameters_t& rhs) const;
	bool operator!=(const reframer_parameters_t& rhs) const;
};

struct reframer_config_t {
	// const version_t version;
	const std::string version;
	const reframer_parameters_t parameters;

	bool operator==(const reframer_config_t& rhs) const;
	bool operator!=(const reframer_config_t& rhs) const;
	reframer_config_t(std::string version, reframer_parameters_t settings):
		version(std::move(version)),parameters(std::move(settings)){};
};

struct date_t {
	int day, month, year;

	bool operator==(const date_t& rhs) const;
	bool operator!=(const date_t& rhs) const;
};

struct scan_t {
	const std::uint64_t reframer_config_index;
	const std::uint64_t rosbag_index;
	const std::string date;
	const std::uint64_t begin_index;
	const std::uint64_t end_index;
	const std::uint64_t point_count;

	bool operator==(const scan_t& rhs) const;
	bool operator!=(const scan_t& rhs) const;

	scan_t(
		std::uint64_t reframer_config_index,
		std::uint64_t rosbag_index,
		std::string date,
		std::uint64_t begin_index,
		std::uint64_t end_index,
		std::uint64_t point_count
	) :
		reframer_config_index(reframer_config_index),
		rosbag_index(rosbag_index),
		date(std::move(date)),
	    begin_index(begin_index),
	    end_index(end_index),
	    point_count(point_count) {};
};

struct metadata_t {
	std::vector<reframer_config_t> configs;
	std::vector<std::string> rosbags;
	std::vector<scan_t> scans;

	bool operator==(const metadata_t& rhs) const;
	bool operator!=(const metadata_t& rhs) const;
};

//[[nodiscard]] version_t get_version() noexcept;

[[nodiscard]] std::string get_version() noexcept;

//[[nodiscard]] date_t get_current_date();

[[nodiscard]] std::string get_current_date();

[[nodiscard]] std::error_code create_empty_meta_json(const std::filesystem::path& filepath) noexcept;

[[nodiscard]] std::error_code write_meta_json(const std::filesystem::path& filepath, metadata_t& output_data) noexcept;

[[nodiscard]] std::error_code read_meta_json_to(
	const std::filesystem::path& filepath, metadata_t& destination
) noexcept;

[[nodiscard]] std::size_t lookup_or_create_rosbag_entry(metadata_t& data, const std::string& bag) noexcept;

[[nodiscard]] std::size_t lookup_or_create_config_entry(metadata_t& data, const reframer_config_t& config) noexcept;

[[nodiscard]] std::uint64_t get_max_frame_id(const metadata_t& metadata) noexcept;

} // namespace metadata

namespace metadata_error {

enum class codes {
	ok = 0,
	missing_meta_json_file
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
