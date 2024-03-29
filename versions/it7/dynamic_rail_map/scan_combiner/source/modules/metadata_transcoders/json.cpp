#include "modules/metadata_transcoders/json.hpp"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"

namespace drm::metadata_transcoders {

bool json::contains_metadata(const std::filesystem::path& directory) noexcept {
	std::error_code error;
	return std::filesystem::exists(directory / filename, error) and not error;
}

enum class value_type {
	BOOL,
	UINT64,
	DOUBLE,
	STRING,
	ARRAY,
	OBJECT
};

template<value_type Type, typename JsonValue>
decltype(auto) get_instance(JsonValue& value) {
	if constexpr (Type == value_type::BOOL) {
		if (value.IsBool()) {
			return value.GetBool();
		}
	} else if constexpr (Type == value_type::UINT64) {
		if (value.IsUint64()) {
			return value.GetUint64();
		}
	} else if constexpr (Type == value_type::DOUBLE) {
		if (value.IsDouble()) {
			return value.GetDouble();
		}
	} else if constexpr (Type == value_type::STRING) {
		if (value.IsString()) {
			return value.GetString();
		}
	} else if constexpr (Type == value_type::ARRAY) {
		if (value.IsArray()) {
			return value.GetArray();
		}
	} else if constexpr (Type == value_type::OBJECT) {
		if (value.IsObject()) {
			return value.GetObject();
		}
	} else {
		JsonValue::__unimplemented_type__;
	}
	using namespace json_error;
	throw make_error_code(codes::wrong_type_json);
}

template<value_type Type, typename JsonValue>
decltype(auto) get_member(JsonValue& value, const char* name) {
	if (value.HasMember(name)) {
		return get_instance<Type>(value[name]);
	}
	using namespace json_error;
	throw make_error_code(codes::member_does_not_exist_json);
}

std::error_code json::write(const std::filesystem::path& directory, const metadata::metadata_t& meta) noexcept {

	const auto filepath = directory / filename;

	std::filesystem::remove(filepath);
	rapidjson::Document document;
	document.SetObject();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value scan_combiner_configs(rapidjson::kArrayType);
	for (const auto& config : meta.configs) {
		rapidjson::Value config_val(rapidjson::kObjectType);

		rapidjson::Value version_val;
		version_val.SetString(config.version.c_str(), allocator);
		config_val.AddMember("version", version_val, allocator);

		rapidjson::Value parameters(rapidjson::kObjectType);
		{
			rapidjson::Value lidar_topic;
			lidar_topic.SetString(config.parameters.lidar_topic.c_str(), allocator);
			parameters.AddMember("lidar_topic", lidar_topic, allocator);

			rapidjson::Value relative_begin_time;
			relative_begin_time.SetUint64(config.parameters.relative_begin_time.count());
			parameters.AddMember("relative_begin_time", relative_begin_time, allocator);

			rapidjson::Value relative_end_time;
			relative_end_time.SetUint64(config.parameters.relative_end_time.count());
			parameters.AddMember("relative_end_time", relative_end_time, allocator);

			rapidjson::Value origin_ignore_radius;
			origin_ignore_radius.SetDouble(config.parameters.origin_ignore_radius);
			parameters.AddMember("origin_ignore_radius", origin_ignore_radius, allocator);

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
		scan_combiner_configs.PushBack(config_val, allocator);
	}
	document.AddMember("scan_combiner_configs", scan_combiner_configs, allocator);

	rapidjson::Value rosbags(rapidjson::kArrayType);
	for (const auto& rosbag_data : meta.rosbags) {
		rapidjson::Value rosbag_value(rapidjson::kObjectType);

		rapidjson::Value rosbag_name;
		rosbag_name.SetString(rosbag_data.name.c_str(), allocator);
		rosbag_value.AddMember("name", rosbag_name, allocator);

		rapidjson::Value rosbag_begin_time;
		rosbag_begin_time.SetUint64(rosbag_data.begin_time.count());
		rosbag_value.AddMember("begin_time", rosbag_begin_time, allocator);

		rapidjson::Value rosbag_end_time;
		rosbag_end_time.SetUint64(rosbag_data.end_time.count());
		rosbag_value.AddMember("end_time", rosbag_end_time, allocator);

		rosbags.PushBack(rosbag_value, allocator);
	}
	document.AddMember("rosbags", rosbags, allocator);

	rapidjson::Value scans(rapidjson::kArrayType);
	for (const auto& scan : meta.scans) {
		rapidjson::Value scan_val(rapidjson::kObjectType);

		rapidjson::Value scan_combiner_config_index;
		scan_combiner_config_index.SetUint64(scan.scan_combiner_config_index);
		scan_val.AddMember("scan_combiner_config_index", scan_combiner_config_index, allocator);

		rapidjson::Value rosbag_index;
		rosbag_index.SetUint64(scan.rosbag_index);
		scan_val.AddMember("rosbag_index", rosbag_index, allocator);

		rapidjson::Value timestamp;
		timestamp.SetUint64(scan.timestamp.count());
		scan_val.AddMember("timestamp", timestamp, allocator);

		rapidjson::Value begin_index;
		begin_index.SetUint64(scan.frame_range.begin_index);
		scan_val.AddMember("begin_index", begin_index, allocator);

		rapidjson::Value end_index;
		end_index.SetUint64(scan.frame_range.end_index);
		scan_val.AddMember("end_index", end_index, allocator);

		rapidjson::Value point_count;
		point_count.SetUint64(scan.point_count);
		scan_val.AddMember("point_count", point_count, allocator);

		scans.PushBack(scan_val, allocator);
	}
	document.AddMember("scans", scans, allocator);

	std::ofstream ofs(filepath);
	if (not ofs) {
		return { errno, std::system_category() };
	}
	rapidjson::OStreamWrapper osw(ofs);

	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	document.Accept(writer);

	return {};
}

std::error_code json::read(const std::filesystem::path& directory, metadata::metadata_t& meta) noexcept {
	const auto filepath = directory / filename;

	std::ifstream ifs(filepath);
	if (not ifs) {
		return { errno, std::system_category() };
	}
	try {
		rapidjson::IStreamWrapper isw(ifs);

		rapidjson::Document document;
		document.ParseStream(isw);

		for (auto& config : get_member<value_type::ARRAY>(document, "scan_combiner_configs")) {
			const auto version = std::string(get_member<value_type::STRING>(config, "version"));
			{
				const rapidjson::Value& parameters_val = get_member<value_type::OBJECT>(config, "parameters");

				const auto lidar_topic = std::string(get_member<value_type::STRING>(parameters_val, "lidar_topic")
				);
				const auto relative_begin_time = types::timestamp_t(
					get_member<value_type::UINT64>(parameters_val, "relative_begin_time")
				);
				const auto relative_end_time = types::timestamp_t(
					get_member<value_type::UINT64>(parameters_val, "relative_end_time")
				);
				const auto origin_ignore_radius = get_member<value_type::DOUBLE>(
					parameters_val,
					"origin_ignore_radius"
				);
				const auto max_scan_position_deviation = get_member<value_type::DOUBLE>(
					parameters_val,
					"max_scan_position_deviation"
				);
				const auto max_radial_distance = get_member<value_type::DOUBLE>(parameters_val, "max_radial_distance");
				const auto max_peripheral_distance = get_member<value_type::DOUBLE>(
					parameters_val,
					"max_peripheral_distance"
				);

				metadata::scan_combiner_parameters_t parameters = { std::move(lidar_topic),
					                                                relative_begin_time,
					                                                relative_end_time,
					                                                origin_ignore_radius,
					                                                max_scan_position_deviation,
					                                                max_radial_distance,
					                                                max_peripheral_distance };
				meta.configs.emplace_back(std::move(version), parameters);
			}
		}

		for (auto& bag : get_member<value_type::ARRAY>(document, "rosbags")) {
			const auto name = std::string(get_member<value_type::STRING>(bag, "name"));
			const auto begin_time = types::timestamp_milli_t(get_member<value_type::UINT64>(bag, "begin_time"));
			const auto end_time = types::timestamp_milli_t(get_member<value_type::UINT64>(bag, "end_time"));
			meta.rosbags.emplace_back(std::move(name), begin_time, end_time);
		}

		for (auto& scan : get_member<value_type::ARRAY>(document, "scans")) {
			const auto scan_combiner_config_index = get_member<value_type::UINT64>(scan, "scan_combiner_config_index");
			const auto rosbag_index = get_member<value_type::UINT64>(scan, "rosbag_index");
			const auto timestamp = types::timestamp_milli_t(get_member<value_type::UINT64>(scan, "timestamp"));
			const auto begin_index = get_member<value_type::UINT64>(scan, "begin_index");
			const auto end_index = get_member<value_type::UINT64>(scan, "end_index");
			const auto point_count = get_member<value_type::UINT64>(scan, "point_count");

			meta.scans.emplace_back(
				scan_combiner_config_index,
				rosbag_index,
				timestamp,
				metadata::frame_range_t{ begin_index, end_index },
				point_count
			);
		}
	} catch (std::error_code error_code) {
		return error_code;
	}
	return {};
}

namespace json_error {

const char* category::name() const noexcept {
	return "metadata_json";
}

std::string category::message(int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::member_does_not_exist_json:
		return "Der Eintrag, der angefragt wurde, existiert in der gelesenen JSON-Datei nicht.";
	case codes::wrong_type_json:
		return "Der Datentyp, der von einem Eintrag gelesen werden sollte, ist inkorrekt.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_code make_error_code(codes e) noexcept {
	return { static_cast<int>(e), json_error_category() };
}

} // namespace json_error

std::error_category& json_error_category() noexcept {
	static json_error::category category;
	return category;
}

} // namespace drm::metadata_transcoders
