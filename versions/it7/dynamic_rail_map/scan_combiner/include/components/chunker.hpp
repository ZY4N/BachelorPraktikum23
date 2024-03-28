#pragma once

#include "config/types.hpp"

namespace drm {

/**
 * @class chunker
 * @brief A class for sorting points into chunks based on their horizontal distribution.
 */
class chunker {
private:
	using hash_t = std::uint32_t;
	static constexpr auto coord_max = std::numeric_limits<types::chunk_coord_t>::max();
	static constexpr auto invalid_chunk_pos = types::chunk_pos_t{ coord_max, coord_max };

	static inline constexpr std::size_t point_bucket_default_size = 8 * 1'024;
	static inline constexpr std::size_t point_bucket_max_size = point_bucket_default_size * 2;

	struct chunk_point_bucket_t {
		std::vector<drm::types::translation_t> points;
		types::chunk_pos_t prev_chunk_pos;
		std::uint8_t num_chunks; // 0 -> no points, 1 -> one chunk, 2-3 -> n > 1 chunks
	};

public:
	/**
	 * @brief Constructs a chunker instance with the specified quad tree order.
	 *
	 * This constructor initializes a chunker object with the given quad tree order. It calculates the number
	 * of buckets based on the quad tree order and allocates memory for the buckets accordingly.
	 *
	 * @param quad_tree_order The order of the quad tree used for bucketing points.
	 *
	 * This function calculates the number of buckets based on the quad tree order using the formula:
	 * @c num_buckets = 2^(2 * @c quad_tree_order).
	 * It then allocates the buckets and initializes the buckets buffers with default capacities.
	 */
	explicit chunker(std::uint32_t quad_tree_order);

	/**
	 * @brief Sorts the given points into chunks based on the provided transformation and chunk size.
	 *
	 * This function clears any existing buckets to prepare for the new chunking operation. It then sorts the given
	 * points into buckets using a simple spacial hash function. Finally, it creates chunks from these buckets,
	 * applying the provided transformation (pose) inverted to the points before adding them to the chunks vector.
	 *
	 * @param pose       The sensor transformation with which the points were captured.
	 * @param points     The captured points in sensor space.
	 * @param chunk_size The side length of one chunk in meters.
	 * @param chunks     The list of chunk data to be written to.
	 */
	void process(
		const types::transform_t& pose,
		tcb::span<const types::timed_point_t> points,
		const double& chunk_size,
		std::vector<types::chunk_t>& chunks
	);

protected:
	[[nodiscard]] static types::chunk_pos_t calc_chunk_position(
		const types::translation_t& position, const double& chunk_size
	);

	hash_t calc_spacial_hash(const types::chunk_pos_t& pos) const;

	void clear_buckets();

	void sort_points_in_buckets(tcb::span<const types::timed_point_t> times_points, const double& chunk_size);

	void create_chunks_from_buckets(
		const types::transform_t& pose, const double& chunk_size, std::vector<types::chunk_t>& chunks
	);

private:
	std::vector<chunk_point_bucket_t> m_buckets;
	std::uint32_t m_quad_tree_order;
};

} // namespace drm
