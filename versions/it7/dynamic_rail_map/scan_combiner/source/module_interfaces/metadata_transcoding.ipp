#ifndef INCLUDE_METADATA_TRANSCODING_IMPLEMENTATION
#	error Never include this file directly include 'metadata_transcoding.hpp'
#endif

#include <tuple>

// Include the user defined registration tuple
#include "module_registration/metadata_transcoder_registration.ipp"
#include "util/apply_at_index.hpp"

#include <ostream>

namespace drm::metadata_transcoding {

constexpr auto get_format_name_lookup() {
	return std::apply(
		[](const auto&... transcoder_entries) {
			auto index = std::size_t{};
			return std::array<std::pair<metadata_format, std::string_view>, sizeof...(transcoder_entries)>{
				std::make_pair(metadata_format{ index++ }, std::decay_t<decltype(transcoder_entries)>::format_name)...
			};
		},
		transcoders
	);
}

constexpr std::optional<metadata_format> get_format_by_name(std::string_view name) {
	constexpr auto lookup = get_format_name_lookup();
	for (const auto& [format_type, format_name] : lookup) {
		if (format_name == name) {
			return format_type;
		}
	}
	return { std::nullopt };
}

constexpr std::optional<std::string_view> get_format_name(metadata_format format) {
	constexpr auto lookup = get_format_name_lookup();
	for (const auto& [format_type, format_name] : lookup) {
		if (format_type == format) {
			return format_name;
		}
	}
	return { std::nullopt };
}

bool contains_metadata(metadata_format format, const std::filesystem::path& directory) noexcept {
	auto does_contain_meta = false;

	apply_at_index(
		[&](const auto& transcoder) {
			using transcoder_t = std::decay_t<decltype(transcoder)>;
			does_contain_meta = transcoder_t::contains_metadata(directory);
		},
		transcoders,
		format.index
	);

	return does_contain_meta;
}

std::error_code write(
	metadata_format format, const std::filesystem::path& directory, const metadata::metadata_t& meta
) noexcept {
	auto error = std::error_code{};

	if (not apply_at_index(
			[&](const auto& transcoder) {
				using transcoder_t = std::decay_t<decltype(transcoder)>;
				error = transcoder_t::write(directory, meta);
			},
			transcoders,
			format.index
		)) {
		error = std::make_error_code(std::errc::invalid_argument);
	}

	return error;
}

std::error_code read(
	metadata_format format, const std::filesystem::path& directory, metadata::metadata_t& meta
) noexcept {
	auto error = std::error_code{};

	if (not apply_at_index(
			[&](const auto& transcoder) {
				using transcoder_t = std::decay_t<decltype(transcoder)>;
				error = transcoder_t::read(directory, meta);
			},
			transcoders,
			format.index
		)) {
		error = std::make_error_code(std::errc::invalid_argument);
	}

	return error;
}

} // namespace drm::metadata_transcoding

inline std::ostream& operator<<(std::ostream& out, const drm::metadata_transcoding::metadata_format format) {

	const auto name_opt = drm::metadata_transcoding::get_format_name(format);
	if (name_opt) {
		out << *name_opt;
	} else {
		out << "unknown(" << std::to_string(static_cast<int>(format.index)) << ")";
	}

	return out;
}
