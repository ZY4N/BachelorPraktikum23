#include "modules/metadata.hpp"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include "util/logger.hpp"
#include "version.hpp"

#include <fstream>

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

/*
version_t get_version() noexcept {
    return { version::major, version::minor, version::revision };
}
*/

std::string get_version() noexcept {
	std::stringstream stream{};
	stream << version::major << "." << version::minor << "." << version::revision;
	return { stream.str() };
}

/*
date_t get_current_date() {
    using namespace drm::metadata_error;

    auto tp = std::chrono::system_clock::now();
    auto in_time = std::chrono::system_clock::to_time_t(tp);
    auto local_time = std::localtime(&in_time);

    return { local_time->tm_mday, local_time->tm_mon, local_time->tm_year };
}
*/

std::string get_current_date() {
	using namespace drm::metadata_error;

	auto tp = std::chrono::system_clock::now();
	auto in_time = std::chrono::system_clock::to_time_t(tp);
	auto local_time = std::localtime(&in_time);

	std::stringstream stream{};
	stream << std::put_time(local_time, "%d.%m.%Y");
	return { stream.str() };
}

[[nodiscard]] std::error_code create_empty_meta_json(const std::filesystem::path& filepath) noexcept {
	rapidjson::Document document;
	document.SetObject();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value reframer_configs(rapidjson::kArrayType);
	document.AddMember("reframer_configs", reframer_configs, allocator);
	rapidjson::Value rosbags(rapidjson::kArrayType);
	document.AddMember("rosbags", rosbags, allocator);
	rapidjson::Value scans(rapidjson::kArrayType);
	document.AddMember("scans", scans, allocator);

	std::ofstream ofs(filepath);
	rapidjson::OStreamWrapper osw(ofs);

	rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
	document.Accept(writer);

	return {};
}

[[nodiscard]] std::error_code write_meta_json(const std::filesystem::path& filepath, metadata_t& output_data) noexcept {
	std::filesystem::remove(filepath);
	rapidjson::Document document;
	document.SetObject();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value reframer_configs(rapidjson::kArrayType);
	for (const auto& config : output_data.configs) {
		rapidjson::Value config_val(rapidjson::kObjectType);

		rapidjson::Value version_val;
		version_val.SetString(config.version.c_str(), allocator);
		config_val.AddMember("version", version_val, allocator);

		rapidjson::Value parameters(rapidjson::kObjectType);
		{
			rapidjson::Value topics(rapidjson::kArrayType);
			for (const auto& topic : config.parameters.lidar_topics_vector) {
				rapidjson::Value topic_val;
				topic_val.SetString(topic.c_str(), allocator);
				topics.PushBack(topic_val, allocator);
			}
			parameters.AddMember("topics", topics, allocator);

			rapidjson::Value relative_begin_time;
			relative_begin_time.SetUint64(config.parameters.relative_begin_time.count());
			parameters.AddMember("relative_begin_time", relative_begin_time, allocator);

			rapidjson::Value relative_end_time;
			relative_end_time.SetUint64(config.parameters.relative_end_time.count());
			parameters.AddMember("relative_end_time", relative_end_time, allocator);

			rapidjson::Value max_position_deviation;
			max_position_deviation.SetDouble(config.parameters.max_position_deviation);
			parameters.AddMember("max_position_deviation", max_position_deviation, allocator);

			rapidjson::Value max_scan_position_deviation;
			max_scan_position_deviation.SetDouble(config.parameters.max_scan_position_deviation);
			parameters.AddMember("max_scan_position_deviation", max_scan_position_deviation, allocator);

			rapidjson::Value max_radial_distance;
			max_radial_distance.SetDouble(config.parameters.max_radial_distance);
			parameters.AddMember("max_radial_distance", max_radial_distance, allocator);

			rapidjson::Value max_peripheral_distance;
			max_peripheral_distance.SetDouble(config.parameters.max_peripheral_distance);
			parameters.AddMember("max_peripheral_distance", max_peripheral_distance, allocator);
		}
		config_val.AddMember("parameters", parameters, allocator);
		reframer_configs.PushBack(config_val, allocator);
	}
	document.AddMember("reframer_configs", reframer_configs, allocator);

	rapidjson::Value rosbags(rapidjson::kArrayType);
	for (const auto& rosbag_name : output_data.rosbags) {
		rapidjson::Value str_val;
		str_val.SetString(rosbag_name.c_str(), allocator);
		rosbags.PushBack(str_val, allocator);
	}
	document.AddMember("rosbags", rosbags, allocator);

	rapidjson::Value scans(rapidjson::kArrayType);
	for (const auto& scan : output_data.scans) {
		rapidjson::Value scan_val(rapidjson::kObjectType);

		rapidjson::Value reframer_config_index;
		reframer_config_index.SetUint64(scan.reframer_config_index);
		scan_val.AddMember("reframer_config_index", reframer_config_index, allocator);

		rapidjson::Value rosbag_index;
		rosbag_index.SetUint64(scan.rosbag_index);
		scan_val.AddMember("rosbag_index", rosbag_index, allocator);

		rapidjson::Value date_val;
		date_val.SetString(scan.date.c_str(), allocator);
		scan_val.AddMember("date", date_val, allocator);

		rapidjson::Value begin_index;
		begin_index.SetUint64(scan.begin_index);
		scan_val.AddMember("begin_index", begin_index, allocator);

		rapidjson::Value end_index;
		end_index.SetUint64(scan.end_index);
		scan_val.AddMember("end_index", end_index, allocator);

		rapidjson::Value point_count;
		point_count.SetUint64(scan.point_count);
		scan_val.AddMember("point_count", point_count, allocator);

		scans.PushBack(scan_val, allocator);
	}
	document.AddMember("scans", scans, allocator);

	std::ofstream ofs(filepath);
	rapidjson::OStreamWrapper osw(ofs);

	rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
	document.Accept(writer);

	return {};
}

[[nodiscard]] std::error_code read_meta_json_to(
	const std::filesystem::path& filepath, metadata_t& destination
) noexcept {
	std::ifstream ifs(filepath);
	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document document;
	document.ParseStream(isw);

	const rapidjson::Value& reframer_configs = document["reframer_configs"];
	for (auto& config : reframer_configs.GetArray()) {
		const std::string version = config["version"].GetString();
		{
			const rapidjson::Value& parameters_val = config["parameters"];
			std::vector<std::string> lidar_topics_vector{};
			for (auto& topics : parameters_val["topics"].GetArray()) {
				lidar_topics_vector.emplace_back(topics.GetString());
			}
			const types::timestamp_t relative_begin_time{ parameters_val["relative_begin_time"].GetUint64() };
			const types::timestamp_t relative_end_time{ parameters_val["relative_end_time"].GetUint64() };
			const double max_position_deviation = parameters_val["max_position_deviation"].GetDouble();
			const double max_scan_position_deviation = parameters_val["max_scan_position_deviation"].GetDouble();
			const double max_radial_distance = parameters_val["max_radial_distance"].GetDouble();
			const double max_peripheral_distance = parameters_val["max_peripheral_distance"].GetDouble();

			reframer_parameters_t parameters = { lidar_topics_vector,         relative_begin_time,
				                                 relative_end_time,           max_position_deviation,
				                                 max_scan_position_deviation, max_radial_distance,
				                                 max_peripheral_distance };
			destination.configs.emplace_back(version, parameters);
		}
	}

	const rapidjson::Value& rosbags = document["rosbags"];
	for (auto& bag : rosbags.GetArray()) {
		destination.rosbags.emplace_back(bag.GetString());
	}
	const rapidjson::Value& scans = document["scans"];
	for (auto& scan : scans.GetArray()) {
		const std::uint64_t reframer_config_index = scan["reframer_config_index"].GetUint64();
		const std::uint64_t rosbag_index = scan["rosbag_index"].GetUint64();
		const std::string date = scan["date"].GetString();
		const std::uint64_t begin_index = scan["begin_index"].GetUint64();
		const std::uint64_t end_index = scan["end_index"].GetUint64();
		const std::uint64_t point_count = scan["point_count"].GetUint64();

		destination.scans.emplace_back(reframer_config_index, rosbag_index, date, begin_index, end_index, point_count);
	}

	return {};
}

std::size_t lookup_or_create_rosbag_entry(metadata_t& data, const std::string& bag) noexcept {
	const auto entry_it = std::find(data.rosbags.begin(), data.rosbags.end(), bag);
	const auto index = static_cast<std::size_t>(entry_it - data.rosbags.begin());
	if (index == data.rosbags.size()) {
		data.rosbags.emplace_back(bag);
	}
	return index;
}

std::size_t lookup_or_create_config_entry(metadata_t& data, const reframer_config_t& config) noexcept {
	const auto entry_it = std::find(data.configs.begin(), data.configs.end(), config);
	const auto index = static_cast<std::size_t>(entry_it - data.configs.begin());
	if (index == data.configs.size()) {
		data.configs.emplace_back(config);
	}
	return index;
}

std::uint64_t get_max_frame_id(const metadata_t& metadata) noexcept {
	std::uint64_t result = 0;
	for (const auto& scan : metadata.scans) {
		result = std::max(result, scan.end_index);
	}
	return result;
}

bool version_t::operator==(const version_t& rhs) const {
	return major == rhs.major && minor == rhs.minor && revision == rhs.revision;
}

bool version_t::operator!=(const version_t& rhs) const {
	return !(rhs == *this);
}

bool reframer_parameters_t::operator==(const reframer_parameters_t& rhs) const {
	return lidar_topics_vector == rhs.lidar_topics_vector && relative_begin_time == rhs.relative_begin_time &&
		relative_end_time == rhs.relative_end_time && max_position_deviation == rhs.max_position_deviation &&
		max_scan_position_deviation == rhs.max_scan_position_deviation &&
		max_radial_distance == rhs.max_radial_distance && max_peripheral_distance == rhs.max_peripheral_distance;
}

bool reframer_parameters_t::operator!=(const reframer_parameters_t& rhs) const {
	return !(rhs == *this);
}

bool reframer_config_t::operator==(const reframer_config_t& rhs) const {
	return version == rhs.version && parameters == rhs.parameters;
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
	return reframer_config_index == rhs.reframer_config_index && rosbag_index == rhs.rosbag_index && date == rhs.date &&
		begin_index == rhs.begin_index && end_index == rhs.end_index && point_count == rhs.point_count;
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
