#pragma once

#include <chrono>
#include <string>
#include <vector>
#include "Eigen/Geometry"
#include "span.hpp"


namespace drm::types {

using timestamp_t = std::chrono::duration<std::uint64_t, std::nano>;

using translation_t = Eigen::Vector3d;
using rotation_t = Eigen::Quaterniond;
using matrix_t = Eigen::Isometry3d;

struct transform_t {
	translation_t translation;
	rotation_t rotation;
};

struct timed_transform_t {
	transform_t transform;
	timestamp_t timestamp;
};

struct timed_velocity_t {
	double velocity;
	timestamp_t timestamp;
};

struct timed_point_t {
	inline timed_point_t(const translation_t& new_position, const timestamp_t& new_timestamp) :
		position{ new_position }, timestamp{ new_timestamp } {
	}

	translation_t position;
	timestamp_t timestamp;
};

struct lidar_scan_t {
	inline lidar_scan_t(
		std::string new_string, const transform_t& new_transform, const std::vector<timed_point_t>& new_timed_points
	) :
		sensor_name{ std::move(new_string) }, sensor_to_tram_space{ new_transform }, timed_points{ new_timed_points } {
	}

	std::string sensor_name;
	transform_t sensor_to_tram_space;
	std::vector<timed_point_t> timed_points;
};

struct lidar_frame_t {
	inline lidar_frame_t(
		const transform_t& new_pose, const tcb::span<timed_point_t>& new_points
	) :
		pose{ new_pose }, points{ new_points } {
	}

	transform_t pose;
	tcb::span<timed_point_t> points;
};

} // namespace drm::types