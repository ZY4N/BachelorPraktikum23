#pragma once

#include "modules/distance_filtering.hpp"
#include "types.hpp"
#include "unbagger.hpp"

#include <deque>
#include <exception>
#include <filesystem>
#include <mutex>

namespace drm {

class lord_tachunker {
private:
	using filter_t = std::remove_reference_t<std::remove_cv_t<
		std::invoke_result_t<decltype(drm::distance_filtering::create_peripheral_filter), double, double>>>;

	struct chunk_point_bucket_t {
		std::vector<drm::types::translation_t> points;
		types::chunk_pos_t prev_chunk_pos;
		std::uint8_t num_chunks; // 0 -> no points, 1 -> one chunk, 2-3 -> n > 1 chunks
	};

	struct segmenting_thread_ctx {
		std::vector<drm::types::lidar_frame_t> frames;
		std::vector<chunk_point_bucket_t> chunk_buckets;
		std::vector<std::pair<types::chunk_pos_t, tcb::span<const drm::types::translation_t>>> frame_segments;
	};

	struct frame_range_t {
		// [ begin_index; end_index [
		std::size_t begin_index{ 0 }, end_index{ 0 };
		inline bool empty() {
			return begin_index == end_index;
		}
		inline void clear() {
			begin_index = end_index;
		}
		inline std::size_t extend() {
			return end_index++;
		}
	};

	struct chunk_meta_entry_t {
		std::size_t num_points{ 0 };
		frame_range_t added_frames{};
	};

	static inline constexpr std::size_t point_bucket_default_size = 8 * 1'024;
	static inline constexpr std::size_t point_bucket_max_size = point_bucket_default_size * 2;

public:
	lord_tachunker(
		const std::vector<std::string>& lidar_topics_vector,
		const size_t& num_threads,
		const types::timestamp_t& relative_begin_time,
		const types::timestamp_t& relative_end_time,
		const types::timestamp_t& time_per_block,
		const types::timestamp_t& transform_padding,
		const double& chunk_size,
		const double& max_position_deviation,
		const double& max_scan_position_deviation,
		const double& max_radial_distance,
		const double& max_peripheral_distance
	);

	[[nodiscard]] std::error_code extract_and_filter(
		const std::filesystem::path& filename, const std::filesystem::path& output_path
	);

protected:
	void setup_segmentation_buffers();

	void segment_frames(segmenting_thread_ctx& ctx, tcb::span<drm::types::lidar_frame_t> frames);

	[[nodiscard]] std::error_code extract_data(
		const types::timestamp_t& begin_time,
		const types::timestamp_t& end_time,
		std::vector<drm::types::timed_transform_t>& transforms,
		std::vector<drm::types::timed_velocity_t>& velocities,
		// std::vector<drm::types::timed_rotation_t>& rotations,
		std::vector<drm::types::timed_point_t>& timed_points,
		drm::types::transform_t& sensor_transform
	);

	[[nodiscard]] std::error_code process_points(
		const std::filesystem::path& output_path,
		segmenting_thread_ctx& ctx,
		tcb::span<const types::timed_transform_t> transforms,
		tcb::span<const types::timed_velocity_t> velocities,
		// tcb::span<const types::timed_rotation_t> rotation,
		tcb::span<types::timed_point_t> timed_points,
		const types::transform_t& sensor_transform
	);

private:
	const std::vector<std::string>& m_lidar_topics_vector;
	const std::size_t m_num_threads;
	const types::timestamp_t m_relative_begin_time;
	const types::timestamp_t m_relative_end_time;
	const types::timestamp_t m_time_per_block;
	const types::timestamp_t m_transform_padding;
	const double m_chunk_size;
	const double m_max_position_deviation;
	const double m_max_scan_position_deviation;
	const double m_max_radial_distance;
	const double m_max_peripheral_distance;

private:
	filter_t m_filter;
	unbagger extractor;
	unsigned int m_chunk_quad_tree_order;
	std::vector<segmenting_thread_ctx> m_segmenting_thread_ctxs;

	std::mutex chunk_pos_lookup_lock;
	std::vector<std::pair<types::chunk_pos_t, std::size_t>> chunk_pos_lookup;
	std::deque<std::pair<std::mutex, chunk_meta_entry_t>> chunk_meta_entries;
};
} // namespace drm
