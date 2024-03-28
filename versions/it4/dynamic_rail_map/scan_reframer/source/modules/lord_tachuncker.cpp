#include "modules/lord_tachuncker.hpp"

#include "lidar_parsers/parse_velodyne_lidar_points.hpp"
#include "modules/frame_exporter.hpp"
#include "modules/reframer.hpp"
#include "modules/unbagger.hpp"
#include "util/logger.hpp"
#include "version.hpp"

namespace drm {

lord_tachuncker::lord_tachuncker(
	const std::vector<std::string>& lidar_topics_vector,
	const size_t& num_threads,
	const types::timestamp_t& relative_begin_time,
	const types::timestamp_t& relative_end_time,
	const types::timestamp_t& time_per_block,
	const types::timestamp_t& transform_padding,
	const double& max_position_deviation,
	const double& max_scan_position_deviation,
	const unsigned int& max_radial_distance,
	const unsigned int& max_peripheral_distance

) :
	m_lidar_topics_vector(lidar_topics_vector),
	m_num_threads(num_threads),
	m_relative_begin_time(relative_begin_time),
	m_relative_end_time(relative_end_time),
	m_time_per_block(time_per_block),
	m_transform_padding(transform_padding),
	m_max_position_deviation(max_position_deviation),
	m_max_scan_position_deviation(max_scan_position_deviation),
	m_filter(drm::distance_filtering::create_peripheral_filter(max_radial_distance, max_peripheral_distance)) {
}

[[nodiscard]] std::error_code lord_tachuncker::extract_and_filter(
	const std::filesystem::path& filename, const std::filesystem::path& output_path, std::size_t& frame_offset
) {

	drm::unbagger extractor{};
	std::error_code error{};
	if ((error = extractor.open(filename))) {
		logger::error("Error while opening rosbag '%': %", filename, error.message());
		return error;
	}

	const auto rosbag_begin = extractor.begin_tim();
	const auto rosbag_end = extractor.end_tim();
	const auto rosbag_duration = rosbag_end - rosbag_begin;

	const auto bag_relative_begin_time = std::min(m_relative_begin_time, rosbag_duration);
	const auto bag_relative_end_time = std::min(m_relative_end_time, rosbag_duration);

	const auto duration_to_be_processed = bag_relative_end_time - bag_relative_begin_time;
	const auto num_blocks = static_cast<std::size_t>(std::ceil(
		std::chrono::duration<double>(duration_to_be_processed) / std::chrono::duration<double>(m_time_per_block)
	));

	for (std::size_t block_index = 0; block_index < num_blocks; block_index++) {
		const auto interval_begin = bag_relative_begin_time + drm::types::timestamp_t(block_index * m_time_per_block);
		const auto interval_end = std::min(interval_begin + m_time_per_block, bag_relative_end_time);

		const auto to_minutes = [](const drm::types::timestamp_t ts) {
			using minutes_t = std::chrono::duration<double, std::ratio<60>>;
			return std::chrono::duration_cast<minutes_t>(ts).count();
		};

		logger::info("Extracting frames from %min to %min", to_minutes(interval_begin), to_minutes(interval_end));

		const auto padded_interval_begin = m_transform_padding < interval_begin ? (interval_begin - m_transform_padding)
																				: interval_begin;
		const auto padded_interval_end = interval_end + m_transform_padding;

		logger::info(
			"padded frames from %min to %min",
			to_minutes(padded_interval_begin),
			to_minutes(padded_interval_end)
		);

		logger::info("Extracting transforms...");
		std::vector<drm::types::timed_transform_t> transforms;
		if ((error = extractor.extract_transforms(
				 transforms,
				 "/tf",
				 "luisenplatz",
				 padded_interval_begin,
				 padded_interval_end,
				 m_max_position_deviation
			 ))) {
			logger::error("Error while extracting transforms: %", error.message());
			continue;
		}
		logger::info("Extracted % transform(s)", transforms.size());

		logger::info("Extracting velocities...");
		std::vector<drm::types::timed_velocity_t> velocities;
		if ((error = extractor.extract_velocities(velocities, "/odom", padded_interval_begin, padded_interval_end))) {
			logger::error("Error while extracting velocities: %", error.message());
			continue;
		}
		logger::info("Extracted % velocities", velocities.size());

		/*logger::info("Extracting rotations...");
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
		logger::info("Extracted % rotation(s)", rotations.size());*/

		logger::info("Extracting lidar points...");
		drm::types::transform_t sensor_transform;
		std::vector<drm::types::timed_point_t> timed_points;
		if ((error = extractor.extract_points_if(
				 m_lidar_topics_vector.at(0),
				 timed_points,
				 sensor_transform,
				 interval_begin,
				 interval_end,
				 drm::lidar_parsers::parse_velodyne_lidar_points<filter_t>,
				 m_filter
			 ))) {
			logger::error("Error while extracting points: %", error.message());
			continue;
		}

		logger::info("Extracted % lidar point(s)", timed_points.size());

		auto reframed_points = tcb::span{ timed_points };

		std::vector<std::vector<drm::types::lidar_frame_t>> thread_frames_containers(m_num_threads);

		const auto min_division_size = reframed_points.size() / m_num_threads;
		const auto num_left = reframed_points.size() % m_num_threads;

		std::vector<std::thread> threads;
		for (std::size_t i = 0; i < m_num_threads; i++) {
			threads.emplace_back([&, index = i]() {
				const auto begin = index * min_division_size + std::min(index, num_left);
				const auto end = begin + min_division_size + (index < num_left);

				auto block_points = reframed_points.subspan(begin, std::min(end, reframed_points.size()) - begin);

				auto& block_frames = thread_frames_containers[index];

				if ((error = drm::reframer::reframe_to_closest_scan_positions(
						 block_points,
						 transforms,
						 velocities,
						 sensor_transform,
						 m_max_scan_position_deviation,
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
		for (auto& thread_frames : thread_frames_containers) {
			frames.insert(frames.end(), thread_frames.begin(), thread_frames.end());
		}

		/*
		if ((error = drm::frame_exporter::write_frames_to_uos_files(output_path, frames, m_num_threads))) {
		    logger::error("Error while exporting frames %", error.message());
		}*/

		if ((error = drm::frame_exporter::write_frames_to_removert_files(
				 output_path,
				 frames,
				 frame_offset,
				 m_num_threads
			 ))) {
			logger::error("Error while exporting frames %", error.message());
		}
		frame_offset += frames.size();
		logger::info("done");
	}

	return error;
}

} // namespace drm
