#pragma once

#include <cassert>
#include <condition_variable>
#include <mutex>
#include <thread>

// WARNING: This implementation should be replaced with the C++20 standard implementation when possible.

/**
 * @class barrier
 * @brief A synchronization primitive that allows a fixed number of threads to wait for each other before proceeding.
 */
class barrier {
public:
	/**
	 * @brief Constructs a barrier with the specified number of threads.
	 *
	 * @param num The number of threads that the barrier will synchronize.
	 */
	inline explicit barrier(std::size_t num) : num_threads(num), wait_count(0), instance(0), mtx(), cv() {
		assert(num != 0);
	}

	inline barrier(const barrier&) = delete;
	inline barrier& operator=(const barrier&) = delete;

	/**
	 * @brief Arrives at the barrier.
	 *
	 * This function is called by each thread to indicate that it has arrived at the synchronization point.
	 * When all threads have arrived, they are all allowed to proceed.
	 */
	inline void arrive() {
		auto lock = std::unique_lock<std::mutex>(mtx);
		if (++wait_count == num_threads) {
			wait_count = 0;
			instance++;
			cv.notify_all();
		}
	}

	/**
	 * @brief Waits at the barrier without arriving.
	 *
	 * This function is called by each thread to wait at the synchronization point until all other threads
	 * have arrived. Once all threads have arrived, they are all allowed to proceed.
	 */
	inline void wait() {
		auto lock = std::unique_lock<std::mutex>(mtx);
		auto inst = instance;
		cv.wait(lock, [this, &inst]() { return instance != inst; });
	}

	/**
	 * @brief Arrives at the barrier and waits.
	 *
	 * This function combines the actions of `arrive()` and `wait()`, allowing a thread to arrive at the
	 * synchronization point and wait for all other threads to arrive before proceeding further.
	 */
	inline void arrive_and_wait() {
		auto lock = std::unique_lock<std::mutex>(mtx);
		auto inst = instance;

		if (++wait_count == num_threads) {
			wait_count = 0;
			instance++;
			cv.notify_all();
		} else {
			cv.wait(lock, [this, &inst]() { return instance != inst; });
		}
	}

private:
	std::size_t num_threads;
	std::size_t wait_count;
	std::size_t instance;
	std::mutex mtx;
	std::condition_variable cv;
};
