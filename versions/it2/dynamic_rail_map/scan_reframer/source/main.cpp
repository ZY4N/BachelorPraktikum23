#include <array>
#include <fstream>
#include <thread>
#include "logger.hpp"
#include "unbagger.hpp"
#include "reframer.hpp"
#include "frame_exporter.hpp"
#include "distance_filtering.hpp"


int main() {

	using namespace std::string_literals;
	const auto lidar_topics = std::array{ "/sensors/lidar/velodyne/velodyne_points"s };

	logger::info("Extracting frames from %", lidar_topics.front());

	const std::size_t num_threads = 48;

	using namespace std::chrono_literals;
	const auto begin_time = 0min;
	const auto end_time = 1h;

	const auto transform_padding = 10s;
	const auto time_per_block = 1h;
	const auto total_time = end_time - begin_time;
	const auto num_blocks = static_cast<std::size_t>(std::ceil(
		std::chrono::duration<double>(total_time) / std::chrono::duration<double>(time_per_block)
	));


	const auto max_scan_position_deviation = 1.0;
	logger::info("Maximum scan position deviation % m", max_scan_position_deviation);

	//const auto filter = drm::distance_filtering::create_simple_filter(50);
	const auto filter = drm::distance_filtering::create_peripheral_filter(30, 20);

	for (const auto filename : {
		"/home/tester/Documents/rosbags/Recorder_2022-08-26-08-59-35_c_l.bag",
		"/home/tester/Documents/rosbags/Recorder_2022-08-26-10-25-02_c_l.bag",
		"/home/tester/Documents/rosbags/Recorder_2022-08-26-12-28-09_c_l.bag",
		"/home/tester/Documents/rosbags/Recorder_2022-08-28-12-28-55_c_l.bag",
		"/home/tester/Documents/rosbags/Recorder_2022-08-28-13-49-15_c_l.bag"
	}) {

		logger::info("Opening rosbag from '%'", filename);
		drm::unbagger extractor{};
		std::error_code error;
		if ((error = extractor.open(filename))) {
			logger::error("Error while opening rosbag '%': %", filename, error.message());
			continue;
		}

		for (std::size_t block_index = 0; block_index < num_blocks; block_index++) {
			const auto interval_begin = drm::types::timestamp_t(block_index * time_per_block);
			const auto interval_end = std::min(interval_begin + time_per_block, drm::types::timestamp_t(end_time));

			logger::info("Extracting frames from % to %", interval_begin.count(), interval_end.count());

			const auto padded_interval_begin = transform_padding < interval_begin
				? (interval_begin - transform_padding)
				: interval_begin;
			const auto padded_interval_end = interval_end + transform_padding;

			logger::info("padded frames from % to %", padded_interval_begin.count(), padded_interval_end.count());

			logger::info("Extracting transforms");
			std::vector<drm::types::timed_transform_t> transforms;
			if ((
				error = extractor
					.extract_transforms(transforms, "/tf", "luisenplatz", padded_interval_begin, padded_interval_end)
			)) {
				logger::error("Error while extracting transforms: %", error.message());
				continue;
			}
			logger::info("Extracted % transforms", transforms.size());

			logger::info("Extracting velocities");
			std::vector<drm::types::timed_velocity_t> velocities;
			if ((
				error = extractor.extract_velocities(velocities, "/odom", padded_interval_begin, padded_interval_end)
			)) {
				logger::error("Error while extracting velocities: %", error.message());
				continue;
			}
			logger::info("Extracted % velocities", velocities.size());

			logger::info("Extracting lidar scans");
			std::vector<drm::types::lidar_scan_t> scans;
			if ((
				error = extractor
					.extract_lidar_scan_if(lidar_topics, scans, interval_begin, interval_end, filter)
			)) {
				logger::error("Error while extracting points: %", error.message());
				continue;
			}

			for (auto& [sensor_name, sensor_transform, points] : scans) {
				logger::info("Extracted % points from %", points.size(), sensor_name);

				auto reframed_points = tcb::span{ points };


				std::vector<std::vector<drm::types::lidar_frame_t>> thread_frames(num_threads);

				const auto min_division_size = points.size() / num_threads;
				const auto num_left = points.size() % num_threads;

				std::vector<std::thread> threads;
				for (std::size_t i = 0; i < num_threads; i++) {
					threads.emplace_back(
						[&, index = i]() {
							const auto begin = index * min_division_size + std::min(index, num_left);
							const auto end = begin + min_division_size + (index < num_left);

							auto block_points = reframed_points.subspan(
								begin, std::min(end, reframed_points.size()) - begin
							);

							auto& block_frames = thread_frames[index];

							if ((
								error = drm::reframer::reframe_to_closest_scan_positions(
									block_points, transforms, velocities, sensor_transform, max_scan_position_deviation,
									block_frames
								)
							)) {
								logger::warn("Error in thread % while reframing: %", index, error.message());
							}
						}
					);
				}

				for (auto& thread : threads) {
					thread.join();
				}

				std::vector<drm::types::lidar_frame_t> frames;
				for (auto& thread_frame : thread_frames) {
					frames.insert(frames.end(), thread_frame.begin(), thread_frame.end());
				}

				if (
					(
						error = drm::frame_exporter::write_frames_to_uos_files(
							"/tmp/map_data", frames, num_threads
						)
					)
					) {
					logger::error("Error while exporting frames %", error.message());
				}

				logger::info("Actually bloody done or what?!?");
			}
		}
	}
}
