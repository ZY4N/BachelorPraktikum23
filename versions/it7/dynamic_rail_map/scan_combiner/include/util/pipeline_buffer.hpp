#pragma once

#include "barrier.hpp"

#include <cassert>
#include <cinttypes>
#include <mutex>
#include <utility>

/**
 * @class pipeline_buffer
 * @brief A class representing a pipeline buffer with synchronization capabilities.
 *
 * @tparam T The type of data stored in the pipeline buffer.
 * @tparam N The size of the pipeline buffer.
 */
template<typename T, std::size_t N>
class pipeline_buffer {
public:
	using value_type = T;
	static constexpr auto size = N;

	/**
	 * @brief Constructs a pipeline buffer with optional initial values.
	 *
	 * @tparam Args The types of arguments used for initialization.
	 * @param args  The arguments used for initialization.
	 */
	template<typename... Args>
	explicit pipeline_buffer(Args&&... args) :
		pipeline_buffer(std::make_index_sequence<N>{}, std::forward<Args>(args)...) {
	}

private:
	template<std::size_t... Is, typename... Args>
	explicit pipeline_buffer(std::index_sequence<Is...>, Args&&... args) :
		buffers{ args... }, barriers{ ((void)Is, barrier(2))... } {
		for (auto& barrier : barriers) {
			barrier.arrive();
		}
	}

public:
	/**
	 * @brief Returns the index of the input buffer.
	 *
	 * @param index The index of the current buffer in the pipeline.
	 *
	 * @return The index of the input buffer in the pipeline.
	 */
	[[nodiscard]] inline constexpr static std::size_t input_buffer(const std::size_t index) {
		return (index + 1) % size;
	}

	/**
	 * @brief Acquires the buffer at the specified index.
	 *
	 * @param index The index of the buffer to acquire.
	 *
	 * @return A reference to the acquired buffer.
	 */
	inline value_type& acquire(const std::size_t index) {
		mtxs[index].lock();
		barriers[index].arrive();
		return buffers[index];
	}

	/**
	 * @brief Releases the buffer at the specified index.
	 *
	 * @param index The index of the buffer to release.
	 */
	inline void release(const std::size_t index) {
		mtxs[index].unlock();
		barriers[index].arrive();
	}

	/**
	 * @brief Hands off the buffer at the specified index.
	 *
	 * Hands off the buffer at the specified index in the pipeline. This operation unlocks the mutex
	 * associated with the buffer and waits for the corresponding barrier to synchronize with other
	 * buffers in the pipeline before further processing.
	 *
	 * @param index The index of the buffer to hand off.
	 */
	inline void handoff(const std::size_t index) {
		mtxs[index].unlock();
		barriers[index].arrive_and_wait();
	}

private:
	std::array<value_type, size> buffers;
	std::array<std::mutex, size> mtxs{};
	std::array<barrier, size> barriers;
};
