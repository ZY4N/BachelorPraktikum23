#pragma once

#include "Eigen/Geometry"
#include "span.hpp"

#include <chrono>
#include <string>
#include <vector>

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

struct timed_rotation_t {
	rotation_t rotation;
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

struct lidar_frame_t {
	inline lidar_frame_t(const transform_t& new_pose, const tcb::span<timed_point_t>& new_points) :
		pose{ new_pose }, points{ new_points } {
	}

	transform_t pose;
	tcb::span<timed_point_t> points;
};

} // namespace drm::types
