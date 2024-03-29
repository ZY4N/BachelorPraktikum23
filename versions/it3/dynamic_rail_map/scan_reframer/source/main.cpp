#include "lidar_parsers/parse_velodyne_lidar_points.hpp"
#include "modules/distance_filtering.hpp"
#include "modules/frame_exporter.hpp"
#include "modules/reframer.hpp"
#include "modules/unbagger.hpp"
#include "util/logger.hpp"

#include <array>
#include <fstream>
#include <thread>

int main() {

	using namespace std::string_literals;

	const std::size_t num_threads = 48;

	using namespace std::chrono_literals;
	const auto begin_time = 0min;
	const auto end_time = 1h;

	const auto transform_padding = 10s;
	const auto time_per_block = 2min;
	const auto total_time = end_time - begin_time;
	const auto num_blocks = static_cast<std::size_t>(
		std::ceil(std::chrono::duration<double>(total_time) / std::chrono::duration<double>(time_per_block))
	);

	const auto max_scan_position_deviation = 1.0;
	logger::info("Maximum scan position deviation % m", max_scan_position_deviation);

	// const auto filter = drm::distance_filtering::create_simple_filter(50);
	const auto filter = drm::distance_filtering::create_peripheral_filter(30, 20);
	using filter_t = std::remove_reference_t<std::remove_cv_t<decltype(filter)>>;

	for (const auto filename :
	     { "/home/sera/Documents/RosBags/Recorder_2023-08-01-11-39-20_c_l.bag" }) {

		logger::info("Opening rosbag from '%'", filename);
		drm::unbagger extractor{};
		std::error_code error;
		if ((error = extractor.open(filename))) {
			logger::error("Error while opening rosbag '%': %", filename, error.message());
			continue;
		}

		for (std::size_t block_index{}; block_index < num_blocks; block_index++) {
			const auto interval_begin = drm::types::timestamp_t(block_index * time_per_block);
			const auto interval_end = std::min(interval_begin + time_per_block, drm::types::timestamp_t(end_time));

			logger::info("Extracting frames from % to %", interval_begin.count(), interval_end.count());

			const auto padded_interval_begin = transform_padding < interval_begin ? (interval_begin - transform_padding)
																				  : interval_begin;
			const auto padded_interval_end = interval_end + transform_padding;

			logger::info("padded frames from % to %", padded_interval_begin.count(), padded_interval_end.count());

			logger::info("Extracting transforms");
			std::vector<drm::types::timed_transform_t> transforms;
			if ((error = extractor.extract_transforms(
					 transforms,
					 "/tf",
					 "luisenplatz",
					 padded_interval_begin,
					 padded_interval_end
				 ))) {
				logger::error("Error while extracting transforms: %", error.message());
				continue;
			}
			logger::info("Extracted % transforms", transforms.size());

			logger::info("Extracting velocities");
			std::vector<drm::types::timed_velocity_t> velocities;
			if ((error = extractor.extract_velocities(velocities, "/odom", padded_interval_begin, padded_interval_end)
			    )) {
				logger::error("Error while extracting velocities: %", error.message());
				continue;
			}
			logger::info("Extracted % velocities", velocities.size());

			logger::info("Extracting rotations");
			std::vector<drm::types::timed_rotation_t> rotations;
			if ((error = extractor.extract_imu_data(
					 rotations,
					 "/sensors/piksi/imu",
					 padded_interval_begin,
					 padded_interval_end
				 ))) {
				logger::error("Error while extracting rotations: %", error.message());
				continue;
			}
			logger::info("Extracted % rotations", rotations.size());

			logger::info("Extracting lidar scans");

			drm::types::transform_t sensor_transform;
			std::vector<drm::types::timed_point_t> timed_points;
			if ((error = extractor.extract_points_if(
					 "/sensors/lidar/velodyne/velodyne_points",
					 timed_points,
					 sensor_transform,
					 interval_begin,
					 interval_end,
					 drm::lidar_parsers::parse_velodyne_lidar_points<filter_t>,
					 filter
				 ))) {
				logger::error("Error while extracting points: %", error.message());
				continue;
			}

			logger::info("Extracted % points", timed_points.size());

			auto reframed_points = tcb::span{ timed_points };

			std::vector<std::vector<drm::types::lidar_frame_t>> thread_frames(num_threads);

			const auto min_division_size = reframed_points.size() / num_threads;
			const auto num_left = reframed_points.size() % num_threads;

			std::vector<std::thread> threads;
			for (std::size_t i = 0; i < num_threads; i++) {
				threads.emplace_back([&, index = i]() {
					const auto begin = index * min_division_size + std::min(index, num_left);
					const auto end = begin + min_division_size + (index < num_left);

					auto block_points = reframed_points.subspan(begin, std::min(end, reframed_points.size()) - begin);

					auto& block_frames = thread_frames[index];

					if ((error = drm::reframer::reframe_to_closest_scan_positions(
							 block_points,
							 transforms,
							 velocities,
							 sensor_transform,
							 max_scan_position_deviation,
							 block_frames
						 ))) {
						logger::warn("Error in thread % while reframing: %", index, error.message());
					}
				});
			}

			for (auto& thread : threads) {
				thread.join();
			}

			std::vector<drm::types::lidar_frame_t> frames;
			for (auto& thread_frame : thread_frames) {
				frames.insert(frames.end(), thread_frame.begin(), thread_frame.end());
			}

			if ((error = drm::frame_exporter::write_frames_to_uos_files(
					 "/home/sera/Documents/Old_Outputs/Output_5",
					 frames,
					 num_threads
				 ))) {
				logger::error("Error while exporting frames %", error.message());
			}

			logger::info("done");
		}
	}
}
