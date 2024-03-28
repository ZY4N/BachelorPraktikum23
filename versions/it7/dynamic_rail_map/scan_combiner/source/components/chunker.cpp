#include "components/chunker.hpp"

#include "helpers/transform_conversion.hpp"

#include <cassert>
#include <cmath>

namespace drm {

chunker::chunker(const std::uint32_t quad_tree_order) : m_quad_tree_order{ quad_tree_order } {
	// Calculate quad-tree bucket count from order.
	const auto num_buckets = static_cast<std::uint32_t>(std::pow(2, 2 * quad_tree_order));

	// Allocate buckets.
	m_buckets.resize(num_buckets);
	for (auto& bucket : m_buckets) {
		bucket.points.reserve(point_bucket_default_size);
	}
}

types::chunk_pos_t chunker::calc_chunk_position(const types::translation_t& position, const double& chunk_size) {
	const auto coord_to_index = [&](const double& comp) {
		return static_cast<types::chunk_coord_t>(std::floor(comp / chunk_size));
	};
	return { coord_to_index(position.x()), coord_to_index(position.y()) };
}

chunker::hash_t chunker::calc_spacial_hash(const types::chunk_pos_t& pos) const {
	static const auto hash_mask = std::numeric_limits<hash_t>::max() >> (8 * sizeof(hash_t) - m_quad_tree_order);

	const auto x_comp = static_cast<hash_t>(pos.x) & hash_mask;
	const auto y_comp = static_cast<hash_t>(pos.y) & hash_mask;

	return (x_comp << m_quad_tree_order) | y_comp;
}

void chunker::process(
	const types::transform_t& pose,
	const tcb::span<const types::timed_point_t> points,
	const double& chunk_size,
	std::vector<types::chunk_t>& chunks
) {
	clear_buckets();
	sort_points_in_buckets(points, chunk_size);
	create_chunks_from_buckets(pose, chunk_size, chunks);
}

void chunker::clear_buckets() {
	for (auto& bucket : m_buckets) {
		bucket.points.clear();

		// In case some buckets get too big, reduce their capacity back to the default size.
		if (bucket.points.capacity() > point_bucket_max_size) {
			std::vector<types::translation_t> new_point_vec;
			new_point_vec.reserve(point_bucket_default_size);
			bucket.points.swap(new_point_vec);
		}

		bucket.prev_chunk_pos = invalid_chunk_pos;
		bucket.num_chunks = 0;
	}
}

void chunker::sort_points_in_buckets(tcb::span<const types::timed_point_t> times_points, const double& chunk_size) {
	for (const auto& point : times_points) {
		const auto chunk_pos = calc_chunk_position(point.position, chunk_size);
		const auto bucket_index = calc_spacial_hash(chunk_pos);

		auto& [points, prev_chunk_pos, num_chunks] = m_buckets[bucket_index];
		points.push_back(point.position);

		// Saturate-add to counter.
		num_chunks += chunk_pos != prev_chunk_pos;
		num_chunks = num_chunks == 3 ? 2 : num_chunks;
		prev_chunk_pos = chunk_pos;
	}
}

void chunker::create_chunks_from_buckets(
	const types::transform_t& pose, const double& chunk_size, std::vector<types::chunk_t>& chunks
) {
	const auto sensor_to_dst_space = drm::matrix_from(pose);
	const auto dst_to_sensor_space = sensor_to_dst_space.inverse();

	chunks.reserve(m_buckets.size());
	for (auto& bucket : m_buckets) {
		assert(bucket.points.empty() == (bucket.num_chunks == 0));

		if (bucket.num_chunks == 1) { // most likely case
			chunks.emplace_back(bucket.prev_chunk_pos, bucket.points);
		} else if (bucket.num_chunks > 1) { // very unlikely
			// Sorting can get expensive for larger ranges, so this code only runs
			// if one frame is in more than `num_buckets` chunks or weirdly malformed.
			// In this case the number of points is hopefully small enough
			// to not cause time-complexity issues.
			std::sort(
				bucket.points.begin(),
				bucket.points.end(),
				[&](const types::translation_t& a, const types::translation_t& b) {
					return calc_chunk_position(a, chunk_size) < calc_chunk_position(b, chunk_size);
				}
			);

			auto chunk_begin = bucket.points.cbegin();
			auto chunk_end = chunk_begin;
			auto prev_pos = calc_chunk_position(bucket.points.front(), chunk_size);

			// Find consecutive ranges of chunk points.
			for (const auto& point : bucket.points) {
				const auto chunk_pos = calc_chunk_position(point, chunk_size);
				if (chunk_pos != prev_pos) {
					prev_pos = chunk_pos;
					chunks.emplace_back(prev_pos, tcb::span{ chunk_begin.base(), chunk_end.base() });
					chunk_begin = chunk_end;
				}
				++chunk_end;
			}
			const auto chunk_pos = calc_chunk_position(*chunk_begin, chunk_size);
			chunks.emplace_back(chunk_pos, tcb::span{ chunk_begin.base(), chunk_end.base() });
		}

		// Now that all processing in world coordinates is done,
		// points can be transformed back to sensor space.
		for (auto& point : bucket.points) {
			point = dst_to_sensor_space * point;
		}
	}
}

} // namespace drm
