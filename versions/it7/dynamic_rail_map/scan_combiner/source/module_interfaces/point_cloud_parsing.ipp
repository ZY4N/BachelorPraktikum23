#ifndef INCLUDE_POINT_CLOUD_PARSING_IMPLEMENTATION
#	error Never include this file directly include 'register_point_cloud_parsing.hpp'
#endif

#include <tuple>

// Include the user defined registration tuple
#include "module_registration/point_cloud_parser_registration.ipp"
#include "util/apply_at_index.hpp"

#include <ostream>

namespace drm::point_cloud_parsing {

constexpr auto get_sensor_name_lookup() {
	return std::apply(
		[](const auto&... parsers) {
			auto index = std::size_t{};
			return std::array<std::pair<sensor_type, std::string_view>, sizeof...(parsers)>{
				std::make_pair(sensor_type{ index++ }, std::decay_t<decltype(parsers)>::sensor_name)...
			};
		},
		parsers
	);
}

constexpr std::optional<sensor_type> get_sensor_type_by_name(std::string_view name) {
	constexpr auto lookup = get_sensor_name_lookup();
	for (const auto& [parser_type, parser_name] : lookup) {
		if (parser_name == name) {
			return parser_type;
		}
	}
	return { std::nullopt };
}

constexpr std::optional<std::string_view> get_sensor_name(sensor_type type) {
	constexpr auto lookup = get_sensor_name_lookup();
	for (const auto& [parser_type, parser_name] : lookup) {
		if (parser_type == type) {
			return parser_name;
		}
	}
	return { std::nullopt };
}

template<typename P>
std::error_code parse(
	const sensor_type type,
	rosbag::View& lidar_frames_view,
	std::vector<types::timed_point_t>& timed_points,
	const P& predicate
) noexcept {

	auto error = std::error_code{};

	if (not apply_at_index(
			[&](const auto& parser) {
				using parser_t = std::decay_t<decltype(parser)>;
				error = parser_t::parse(lidar_frames_view, timed_points, predicate);
			},
			parsers,
			type.index
		)) {
		error = std::make_error_code(std::errc::invalid_argument);
	}

	return error;
}
} // namespace drm::point_cloud_parsing

inline std::ostream& operator<<(std::ostream& out, const drm::point_cloud_parsing::sensor_type type) {

	const auto name_opt = drm::point_cloud_parsing::get_sensor_name(type);
	if (name_opt) {
		out << *name_opt;
	} else {
		out << "unknown(" << std::to_string(static_cast<int>(type.index)) << ")";
	}

	return out;
}
