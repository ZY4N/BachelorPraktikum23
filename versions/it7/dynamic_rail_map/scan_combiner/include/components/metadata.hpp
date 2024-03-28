#pragma once

#include "config/types.hpp"
#include "config/version.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace drm {

namespace metadata {

struct scan_combiner_parameters_t {
	const std::string lidar_topic;
	const types::timestamp_t relative_begin_time;
	const types::timestamp_t relative_end_time;
	const double origin_ignore_radius;
	const double max_scan_position_deviation;
	const double max_radial_distance;
	const double max_peripheral_distance;

	bool operator==(const scan_combiner_parameters_t& rhs) const;
	bool operator!=(const scan_combiner_parameters_t& rhs) const;

	scan_combiner_parameters_t(
		std::string lidar_topic,
		types::timestamp_t relative_begin_time,
		types::timestamp_t relative_end_time,
		double origin_ignore_radius,
		double max_scan_position_deviation,
		double max_radial_distance,
		double max_peripheral_distance
	) :
		lidar_topic(std::move(lidar_topic)),
		relative_begin_time(relative_begin_time),
		relative_end_time(relative_end_time),
		origin_ignore_radius(origin_ignore_radius),
		max_scan_position_deviation(max_scan_position_deviation),
		max_radial_distance(max_radial_distance),
		max_peripheral_distance(max_peripheral_distance){};
};

struct scan_combiner_config_t {
	const std::string version;
	const scan_combiner_parameters_t parameters;

	bool operator==(const scan_combiner_config_t& rhs) const;
	bool operator!=(const scan_combiner_config_t& rhs) const;

	scan_combiner_config_t(std::string version, scan_combiner_parameters_t settings) :
		version(std::move(version)), parameters(std::move(settings)){};
};

struct frame_range_t {
	std::uint64_t begin_index{ 0 }, end_index{ 0 };

	bool empty() noexcept;

	void clear() noexcept;

	std::uint64_t extend() noexcept;

	bool operator==(const frame_range_t& other) const noexcept;
};

struct scan_t {
	const std::uint64_t scan_combiner_config_index;
	const std::uint64_t rosbag_index;
	const types::timestamp_milli_t timestamp;
	const frame_range_t frame_range;
	const std::uint64_t point_count;

	bool operator==(const scan_t& rhs) const;
	bool operator!=(const scan_t& rhs) const;

	scan_t(
		std::uint64_t scan_combiner_config_index,
		std::uint64_t rosbag_index,
		types::timestamp_milli_t timestamp,
		const frame_range_t& frame_range,
		std::uint64_t point_count
	) :
		scan_combiner_config_index(scan_combiner_config_index),
		rosbag_index(rosbag_index),
		timestamp(timestamp),
		frame_range(frame_range),
		point_count(point_count){};
};

struct rosbag_metadata_t {
	std::string name{};
	types::timestamp_milli_t begin_time{};
	types::timestamp_milli_t end_time{};

	bool operator==(const rosbag_metadata_t& rhs) const;
	bool operator!=(const rosbag_metadata_t& rhs) const;

	rosbag_metadata_t() = default;
	rosbag_metadata_t(std::string name, types::timestamp_milli_t begin_time, types::timestamp_milli_t end_time) :
		name(std::move(name)), begin_time(begin_time), end_time(end_time){};
};

struct metadata_t {
	std::vector<scan_combiner_config_t> configs;
	std::vector<rosbag_metadata_t> rosbags;
	std::vector<scan_t> scans;

	bool operator==(const metadata_t& rhs) const;
	bool operator!=(const metadata_t& rhs) const;
};

/**
 * @brief Returns the current version as a @c std::string.
 *
 * @return An @c std::string containing the Version in the format "major.minor.revision".
 */
[[nodiscard]] std::string get_version() noexcept;

/**
 * @brief Returns the current time as a unix timestamp represented by a @c std::chrono::duration.
 *
 * @return An @c std::chrono::duration representing the time since the unix epoch in milieseconds.
 */
[[nodiscard]] types::timestamp_milli_t get_timestamp();

/**
 * @brief Returns the highest framerange index.
 *
 * @return An @c std::uint64_t containing the highest end_index from the stored scans.
 */
[[nodiscard]] std::uint64_t get_max_frame_id(const metadata_t& metadata) noexcept;

[[nodiscard]] std::size_t lookup_or_create_rosbag_entry(
	metadata::metadata_t& data, const rosbag_metadata_t& new_bagdata
) noexcept;

[[nodiscard]] std::size_t lookup_or_create_config_entry(
	metadata::metadata_t& data, const metadata::scan_combiner_config_t& config
) noexcept;

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
