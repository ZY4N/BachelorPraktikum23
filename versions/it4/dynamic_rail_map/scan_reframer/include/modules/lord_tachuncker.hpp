#pragma once

#include "modules/distance_filtering.hpp"
#include "types.hpp"

#include <exception>
#include <filesystem>

namespace drm {

class lord_tachuncker {
private:
	using filter_t = std::remove_reference_t<std::remove_cv_t<
		std::invoke_result_t<decltype(drm::distance_filtering::create_peripheral_filter), double, double>>>;

public:
	lord_tachuncker(
		const std::vector<std::string>& lidar_topics_vector,
		const size_t& num_threads,
		const types::timestamp_t& relative_begin_time,
		const types::timestamp_t& relative_end_time,
		const types::timestamp_t& time_per_block,
		const types::timestamp_t& transform_padding,
		const double& max_position_deviation,
		const double& max_scan_position_deviation,
		const unsigned int& max_radial_distance,
		const unsigned int& max_peripheral_distance
	);

	[[nodiscard]] std::error_code extract_and_filter(
		const std::filesystem::path& filename, const std::filesystem::path& output_path, std::size_t& frame_offset
	);

private:
	const std::vector<std::string>& m_lidar_topics_vector;
	const std::size_t m_num_threads;
	const types::timestamp_t m_relative_begin_time;
	const types::timestamp_t m_relative_end_time;
	const types::timestamp_t m_time_per_block;
	const types::timestamp_t m_transform_padding;
	const double m_max_position_deviation;
	const double m_max_scan_position_deviation;
	filter_t m_filter;
};
} // namespace drm
