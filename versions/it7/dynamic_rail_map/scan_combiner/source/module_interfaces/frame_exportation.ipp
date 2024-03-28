#ifndef INCLUDE_FRAME_EXPORTATION_IMPLEMENTATION
#	error Never include this file directly include 'frame_exportation.hpp'
#endif

#include <tuple>

// Include the user defined registration tuple
#include "module_registration/frame_exporter_registration.ipp"
#include "util/apply_at_index.hpp"

#include <ostream>

namespace drm::frame_exportation {

constexpr auto get_format_name_lookup() {
	return std::apply(
		[](const auto&... exporter_entries) {
			auto index = std::size_t{};
			return std::array<std::pair<frame_format, std::string_view>, sizeof...(exporter_entries)>{
				std::make_pair(frame_format{ index++ }, std::decay_t<decltype(exporter_entries)>::format_name)...
			};
		},
		exporters
	);
}

constexpr std::optional<frame_format> get_format_by_name(std::string_view name) {
	constexpr auto lookup = get_format_name_lookup();
	for (const auto& [frame_format, format_name] : lookup) {
		if (format_name == name) {
			return frame_format;
		}
	}
	return { std::nullopt };
}

constexpr std::optional<std::string_view> get_format_name(frame_format format) {
	constexpr auto lookup = get_format_name_lookup();
	for (const auto& [frame_format, format_name] : lookup) {
		if (frame_format == format) {
			return format_name;
		}
	}
	return { std::nullopt };
}

std::error_code write(
	frame_format format,
	const std::filesystem::path& chunk_directory,
	std::mutex& chunk_lock,
	std::size_t frame_index,
	const drm::types::transform_t& pose,
	tcb::span<const types::translation_t> points
) noexcept {
	auto error = std::error_code{};

	if (not apply_at_index(
			[&](const auto& exporter) {
				using exporter_t = std::decay_t<decltype(exporter)>;
				error = exporter_t::write(chunk_directory, chunk_lock, frame_index, pose, points);
			},
			exporters,
			format.index
		)) {
		error = std::make_error_code(std::errc::invalid_argument);
	}

	return error;
}
} // namespace drm::frame_exportation

inline std::ostream& operator<<(std::ostream& out, const drm::frame_exportation::frame_format format) {

	const auto name_opt = drm::frame_exportation::get_format_name(format);
	if (name_opt) {
		out << *name_opt;
	} else {
		out << "unknown(" << std::to_string(static_cast<int>(format.index)) << ")";
	}

	return out;
}
