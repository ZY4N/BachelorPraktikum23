#include "modules/metadata.hpp"

#include "util/logger.hpp"
#include "version.hpp"

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

version_t get_version() noexcept {
	return { version::VERSION_MAJOR, version::VERSION_MINOR, version::VERSION_REVISION };
}

date_t get_current_date() {
	using namespace drm::metadata_error;

	auto tp = std::chrono::system_clock::now();
	auto in_time = std::chrono::system_clock::to_time_t(tp);
	auto local_time = std::localtime(&in_time);

	return { local_time->tm_mday, local_time->tm_mon, local_time->tm_year };
}

std::error_code create_meta_json(const std::filesystem::path& filename) {
	logger::warn("% is not yet implemented and has the following parameter %", "create_meta_json", filename);
	return {};
}

bool version_t::operator==(const version_t& rhs) const {
	return major == rhs.major && minor == rhs.minor && revision == rhs.revision;
}

bool version_t::operator!=(const version_t& rhs) const {
	return !(rhs == *this);
}

bool reframer_settings_t::operator==(const reframer_settings_t& rhs) const {
	return lidar_topics_vector == rhs.lidar_topics_vector && relative_begin_time == rhs.relative_begin_time &&
		relative_end_time == rhs.relative_end_time && max_position_deviation == rhs.max_position_deviation &&
		max_scan_position_deviation == rhs.max_scan_position_deviation &&
		max_radial_distance == rhs.max_radial_distance && max_peripheral_distance == rhs.max_peripheral_distance;
}

bool reframer_settings_t::operator!=(const reframer_settings_t& rhs) const {
	return !(rhs == *this);
}

bool reframer_config_t::operator==(const reframer_config_t& rhs) const {
	return version == rhs.version && settings == rhs.settings;
}

bool reframer_config_t::operator!=(const reframer_config_t& rhs) const {
	return !(rhs == *this);
}

bool date_t::operator==(const date_t& rhs) const {
	return day == rhs.day && month == rhs.month && year == rhs.year;
}

bool date_t::operator!=(const date_t& rhs) const {
	return !(rhs == *this);
}

bool scan_t::operator==(const scan_t& rhs) const {
	return reframer_settings_index == rhs.reframer_settings_index &&
		reframer_config_index == rhs.reframer_config_index && date == rhs.date && bins == rhs.bins;
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
