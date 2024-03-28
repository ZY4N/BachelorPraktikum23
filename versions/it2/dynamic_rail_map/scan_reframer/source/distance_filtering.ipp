#ifndef INCLUDE_DISTANCE_FILTERING_IMPLEMENTATION
#error Never include this file directly include 'distance_filtering.hpp'
#endif

#include "types.hpp"


auto drm::distance_filtering::create_simple_filter(double max_distance) {
	return [max_distance_sq = std::pow(max_distance, 2.0)](const types::translation_t& point) {
		const auto distance_sq = point.squaredNorm();
		return distance_sq <= max_distance_sq;
	};
}

auto drm::distance_filtering::create_peripheral_filter(double max_radial_distance, double max_peripheral_distance) {
	return [
		max_distance_sq = std::pow(max_radial_distance, 2.0),
		max_peripheral_distance_sq = std::pow(max_peripheral_distance, 2.0)
	](const types::translation_t& point) {
		const auto peripheral_distance_sq = point.x() * point.x() + point.z() * point.z();
		const auto radial_distance_sq = point.squaredNorm();
		return radial_distance_sq <= max_distance_sq and peripheral_distance_sq <= max_peripheral_distance_sq;
	};
}