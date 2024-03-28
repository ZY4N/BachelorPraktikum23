#include "components/metadata.hpp"

#include "config/version.hpp"
#include "util/logger.hpp"

const char* drm::metadata_error::category::name() const noexcept {
	return "metadata";
}

std::string drm::metadata_error::category::message(int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_category& drm::metadata_error_category() noexcept {
	static metadata_error::category category;
	return category;
}

std::error_code drm::metadata_error::make_error_code(codes e) noexcept {
	return { static_cast<int>(e), metadata_error_category() };
}

namespace drm::metadata {

std::string get_version() noexcept {
	std::stringstream stream{};
	stream << version::major << "." << version::minor << "." << version::revision;
	return { stream.str() };
}

types::timestamp_milli_t get_timestamp() {
	return std::chrono::duration_cast<types::timestamp_milli_t>(std::chrono::system_clock::now().time_since_epoch());
}

std::uint64_t get_max_frame_id(const metadata_t& metadata) noexcept {
	std::uint64_t result = 0;
	for (const auto& scan : metadata.scans) {
		result = std::max(result, scan.frame_range.end_index);
	}
	return result;
}

std::size_t lookup_or_create_rosbag_entry(metadata_t& data, const rosbag_metadata_t& new_bagdata) noexcept {
	const auto entry_it = std::find(data.rosbags.begin(), data.rosbags.end(), new_bagdata);
	const auto index = static_cast<std::size_t>(entry_it - data.rosbags.begin());
	if (index == data.rosbags.size()) {
		data.rosbags.emplace_back(new_bagdata);
	}
	return index;
}

std::size_t lookup_or_create_config_entry(metadata_t& data, const scan_combiner_config_t& config) noexcept {
	const auto entry_it = std::find(data.configs.begin(), data.configs.end(), config);
	const auto index = static_cast<std::size_t>(entry_it - data.configs.begin());
	if (index == data.configs.size()) {
		data.configs.emplace_back(config);
	}
	return index;
}

bool scan_combiner_parameters_t::operator==(const scan_combiner_parameters_t& rhs) const {
	return lidar_topic == rhs.lidar_topic && relative_begin_time == rhs.relative_begin_time &&
		relative_end_time == rhs.relative_end_time && origin_ignore_radius == rhs.origin_ignore_radius &&
		max_scan_position_deviation == rhs.max_scan_position_deviation &&
		max_radial_distance == rhs.max_radial_distance && max_peripheral_distance == rhs.max_peripheral_distance;
}

bool scan_combiner_parameters_t::operator!=(const scan_combiner_parameters_t& rhs) const {
	return !(rhs == *this);
}

bool scan_combiner_config_t::operator==(const scan_combiner_config_t& rhs) const {
	return version == rhs.version && parameters == rhs.parameters;
}

bool scan_combiner_config_t::operator!=(const scan_combiner_config_t& rhs) const {
	return !(rhs == *this);
}

bool rosbag_metadata_t::operator==(const rosbag_metadata_t& rhs) const {
	return name == rhs.name && begin_time == rhs.begin_time && end_time == rhs.end_time;
}

bool rosbag_metadata_t::operator!=(const rosbag_metadata_t& rhs) const {
	return !(rhs == *this);
}

bool frame_range_t::empty() noexcept {
	return begin_index == end_index;
}

void frame_range_t::clear() noexcept {
	begin_index = end_index;
}

std::uint64_t frame_range_t::extend() noexcept {
	return end_index++;
}

bool frame_range_t::operator==(const frame_range_t& other) const noexcept {
	return this->begin_index == other.begin_index and this->end_index == other.end_index;
}

bool scan_t::operator==(const scan_t& rhs) const {
	return scan_combiner_config_index == rhs.scan_combiner_config_index && rosbag_index == rhs.rosbag_index &&
		timestamp == rhs.timestamp && frame_range == rhs.frame_range && point_count == rhs.point_count;
}

bool scan_t::operator!=(const scan_t& rhs) const {
	return !(rhs == *this);
}

bool metadata_t::operator==(const metadata_t& rhs) const {
	return configs == rhs.configs && rosbags == rhs.rosbags && scans == rhs.scans;
}

bool metadata_t::operator!=(const metadata_t& rhs) const {
	return !(rhs == *this);
}

} // namespace drm::metadata
