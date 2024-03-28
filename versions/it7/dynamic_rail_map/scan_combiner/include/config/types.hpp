#pragma once

#include "Eigen/Geometry"
#include "span.hpp"

#include <chrono>
#include <string>
#include <vector>

namespace drm::types {

using timestamp_t = std::chrono::duration<std::uint64_t, std::nano>;

// I am not using std::chrono::milliseconds to get the *unsinged* int64
using timestamp_milli_t = std::chrono::duration<std::uint64_t, std::milli>;

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

using chunk_coord_t = std::int32_t;

struct chunk_pos_t {
	chunk_coord_t x, y;
};

struct chunk_t {
	inline chunk_t(const chunk_pos_t& new_pos, const tcb::span<const drm::types::translation_t>& new_points) :
		pos{ new_pos }, points{ new_points } {
	}

	chunk_pos_t pos;
	tcb::span<const drm::types::translation_t> points;
};

} // namespace drm::types

inline bool operator==(const drm::types::chunk_pos_t& a, const drm::types::chunk_pos_t& b) {
	return a.x == b.x and a.y == b.y;
}

inline bool operator!=(const drm::types::chunk_pos_t& a, const drm::types::chunk_pos_t& b) {
	return not(a == b);
}

inline bool operator<(const drm::types::chunk_pos_t& a, const drm::types::chunk_pos_t& b) {

	using integer_t = std::uint64_t;

	static_assert(sizeof(drm::types::chunk_pos_t) == sizeof(integer_t));
	static_assert(2 * sizeof(drm::types::chunk_coord_t) == sizeof(integer_t));

	integer_t num_a, num_b;
	std::memcpy(&num_a, &a, sizeof(drm::types::chunk_pos_t));
	std::memcpy(&num_b, &b, sizeof(drm::types::chunk_pos_t));

	return num_a < num_b;
}
