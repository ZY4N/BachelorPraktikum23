#pragma once

#include "components/chunker.hpp"
#include "components/distance_filtering.hpp"
#include "components/metadata.hpp"
#include "components/unbagger.hpp"
#include "config/types.hpp"
#include "module_interfaces/frame_exportation.hpp"
#include "module_interfaces/metadata_transcoding.hpp"
#include "util/barrier.hpp"
#include "util/pipeline_buffer.hpp"

#include <deque>
#include <exception>
#include <filesystem>
#include <mutex>

namespace drm {

/**
 * @class processing_pipeline
 * @brief combines @c scan_combiner components and modules into a multi-threaded pipeline.
 *
 * This class combines the following components:
 * - @c unbagger           for reading rosbags
 * - @c distance_filtering for point filtering
 * - @c reframer           for interpolating and reframing LiDAR frames
 * - @c chunker            for sorting LiDAR frames into chunks
 *
 * and modules:
 * - @c point_cloud_parsing  for parsing LiDAR point cloud messages
 * - @c frame_exporting      for exporting LiDAR frame data
 * - @c metadata_transcoding for reading and writing frame related metadata
 *
 * into a multi-threaded pipeline, combines multiple scans into one continuous map.
 */
class scan_combiner_pipeline {
protected:
	using filter_t = std::decay_t<
		std::invoke_result_t<decltype(drm::distance_filtering::create_peripheral_filter), double, double>>;

	using display_time_t = std::chrono::duration<double, std::ratio<60>>;
	static constexpr auto display_time_unit = "min";

	struct segmenting_thread_ctx {
		segmenting_thread_ctx(std::uint32_t quad_tree_order);
		std::vector<types::lidar_frame_t> frames{};
		std::vector<types::chunk_t> frame_chunks{};
		chunker lord_tachunker;
		std::stringstream chunk_name_stream{};
	};

	struct chunk_meta_entry_t {
		std::size_t num_points{ 0 };
		metadata::frame_range_t added_frames{};
	};

	struct transform_buffer_t {
		std::vector<drm::types::timed_transform_t> timed_transforms;
		std::error_code error;
	};

	struct velocity_buffer_t {
		std::vector<drm::types::timed_velocity_t> timed_velocities;
		std::error_code error;
	};

	struct point_buffer_t {
		std::vector<drm::types::timed_point_t> timed_points;
		drm::types::transform_t sensor_transform;
		metadata::rosbag_metadata_t rosbag_metadata;
		std::error_code error;
	};

	static inline constexpr std::size_t processing_buffer_index_init = 0;
	static inline constexpr std::size_t
		extraction_buffer_index_init = pipeline_buffer<transform_buffer_t, 2>::input_buffer(processing_buffer_index_init
	    );

public:
	/**
	 * @brief constructs a processing_pipeline from the given parameters.
	 *
	 * @param point_processing_thread_multiplier  The number of threads used to process one point data slice.
	 * @param num_point_extraction_threads        The number of threads used for extracting and filtering point data.
	 * @param num_transform_extraction_threads    The number of threads used for extracting transformation data.
	 * @param num_velocity_extraction_threads     The number of threads used for extracting velocity data.
	 * @param metadata_io_threads                 The number of threads used for metadata exportation.
	 * @param lidar_topic                         The LiDAR topic from which point data is parsed.
	 * @param sensor_type                         The sensor type for interpreting the point cloud messages.
	 * @param frame_format                        The frame format to be used for frame exportation.
	 * @param metadata_format                     The metadata format to be used for metadata transcoding.
	 * @param relative_begin_time                 The time limit from rosbag begin time.
	 * @param relative_end_time                   The time offset from rosbag begin time.
	 * @param time_per_block                      The maximum time duration of a continuously processed rosbag block.
	 * @param transform_padding                   The time loaded before and after an interval for spline construction.
	 * @param chunk_size                          The horizontal width and length of a chunk in meters.
	 * @param origin_ignore_radius                Transforms within this radius of the 'luisenplatz' marker will be
	 * ignored.
	 * @param max_scan_position_deviation         The maximum scn position deviation within a reframed LiDAR frame.
	 * @param max_radial_distance                 The maximum radial distance for points from the LiDAR sensor.
	 * @param max_peripheral_distance             The maximum peripheral distance for points from the LiDAR sensor.
	 */
	scan_combiner_pipeline(
		const std::size_t& point_processing_thread_multiplier,
		const std::size_t& num_point_extraction_threads,
		const std::size_t& num_transform_extraction_threads,
		const std::size_t& num_velocity_extraction_threads,
		const std::size_t& metadata_io_threads,
		std::string lidar_topic,
		const point_cloud_parsing::sensor_type& sensor_type,
		const frame_exportation::frame_format& frame_format,
		const metadata_transcoding::metadata_format& metadata_format,
		const types::timestamp_t& relative_begin_time,
		const types::timestamp_t& relative_end_time,
		const types::timestamp_t& time_per_block,
		const types::timestamp_t& transform_padding,
		const double& chunk_size,
		const double& origin_ignore_radius,
		const double& max_scan_position_deviation,
		const double& max_radial_distance,
		const double& max_peripheral_distance
	);

	/**
	 * @brief Processes all provided rosbags and writes resulting chunk data to the @c output_path directory.
	 *
	 * First data ist loaded and filtered from the following topics:
	 * "/tf"           for positional and rotation data of the vehicle
	 * "/odom"         for linear velocities of the vehicle
	 * "/tf_static"    for the "luisenplatz" marker and sensor transformation
	 * "<lidar_topic>" for the LiDAR points
	 *
	 * This data is then interpolated and reframed into point cloud frames.
	 * These frames are sorted into the corresponding chunks and exported with additional metadata.
	 *
	 * @note The output path can contain already processed chunks as long as these have the same chunk size.
	 *
	 * @param filenames   Paths of rosbags to be processed.
	 * @param output_path The map directory to be written to.
	 *
	 * @return An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] std::error_code process_rosbags(
		tcb::span<const std::filesystem::path> filenames, const std::filesystem::path& output_path
	) noexcept;

protected:
	template<class BufferType, class F>
	void extract_all_blocks(
		const logger::config& cfg,
		tcb::span<const std::filesystem::path> filenames,
		pipeline_buffer<BufferType, 2>& double_buffer,
		barrier& buffer_barrier,
		F&& extractor
	) noexcept;

	void extract_all_transform_blocks(
		const logger::config cfg,
		tcb::span<const std::filesystem::path> filenames,
		barrier& buffer_barrier,
		std::size_t thread_index
	) noexcept;

	void extract_all_velocity_blocks(
		const logger::config cfg,
		tcb::span<const std::filesystem::path> filenames,
		barrier& buffer_barrier,
		std::size_t thread_index
	) noexcept;

	void extract_all_point_blocks(
		const logger::config cfg,
		tcb::span<const std::filesystem::path> filenames,
		barrier& buffer_barrier,
		std::size_t thread_index
	) noexcept;

	std::error_code process_all_blocks(
		const metadata::scan_combiner_config_t& meta_config,
		const std::filesystem::path& output_path,
		barrier& buffer_barrier
	) noexcept;

	void process_block(
		const metadata::scan_combiner_config_t& meta_config,
		const std::filesystem::path& output_path,
		const metadata::rosbag_metadata_t& rosbag_metadata,
		tcb::span<drm::types::timed_transform_t> timed_transforms,
		tcb::span<drm::types::timed_velocity_t> timed_velocities,
		tcb::span<point_buffer_t*> point_buffers
	) noexcept;

	[[nodiscard]] std::error_code process_point_block_slice(
		const std::filesystem::path& output_path,
		segmenting_thread_ctx& ctx,
		tcb::span<const types::timed_transform_t> timed_transforms,
		tcb::span<const types::timed_velocity_t> timed_velocities,
		tcb::span<types::timed_point_t> timed_points,
		const types::transform_t& sensor_transform
	) noexcept;

	void write_chunks(
		const std::filesystem::path& output_path,
		std::stringstream& chunk_name_stream,
		const types::transform_t& pose,
		tcb::span<const types::chunk_t> chunks
	) noexcept;

	[[nodiscard]] std::error_code lookup_or_create_chunk_meta_entry(
		types::chunk_pos_t, std::size_t&, std::filesystem::path
	) noexcept;

	void write_meta_data_block(
		const metadata::scan_combiner_config_t& meta_config,
		const std::filesystem::path& output_path,
		const metadata::rosbag_metadata_t& rosbag_metadata,
		std::size_t& num_chunk_entries_left
	) noexcept;

	[[nodiscard]] std::pair<types::timestamp_t, types::timestamp_t> get_to_be_processed_interval(const unbagger& bag
	) noexcept;

	[[nodiscard]] std::pair<types::timestamp_t, types::timestamp_t> pad_spline_interval(
		const types::timestamp_t& min,
		const types::timestamp_t& max,
		const types::timestamp_t& bag_min,
		const types::timestamp_t& bag_max
	) noexcept;

	[[nodiscard]] typename display_time_t::rep to_display_time(const types::timestamp_t& ts);

private:
	const std::size_t m_point_processing_thread_multiplier;
	const std::size_t m_num_point_extraction_threads;
	const std::size_t m_num_transform_extraction_threads;
	const std::size_t m_num_velocity_extraction_threads;
	const std::size_t m_metadata_io_threads;
	const std::string m_lidar_topic;
	const point_cloud_parsing::sensor_type m_lidar_sensor_type;
	const frame_exportation::frame_format m_frame_format;
	const metadata_transcoding::metadata_format m_metadata_format;
	const types::timestamp_t m_relative_begin_time;
	const types::timestamp_t m_relative_end_time;
	const types::timestamp_t m_time_per_block;
	const types::timestamp_t m_transform_padding;
	const double m_chunk_size;
	const double m_origin_ignore_radius;
	const double m_max_scan_position_deviation;
	const double m_max_radial_distance;
	const double m_max_peripheral_distance;

private:
	filter_t m_filter;

	std::vector<segmenting_thread_ctx> m_segmenting_thread_ctxs;

	std::mutex m_chunk_pos_lookup_lock;
	std::vector<std::pair<types::chunk_pos_t, std::size_t>> m_chunk_pos_lookup;
	std::deque<std::pair<std::mutex, chunk_meta_entry_t>> m_chunk_meta_entries;

	std::vector<pipeline_buffer<point_buffer_t, 2>> m_double_point_buffers;
	std::vector<pipeline_buffer<transform_buffer_t, 2>> m_double_transform_buffers;
	std::vector<pipeline_buffer<velocity_buffer_t, 2>> m_double_velocity_buffers;
};

namespace processing_pipeline_error {

enum class codes {
	ok = 0,
	skip_block = 1,
	skip_bag = 2,
	skip_all = 3,
	no_more_data_left
};

struct category : std::error_category {
	[[nodiscard]] const char* name() const noexcept override;

	[[nodiscard]] std::string message(int ev) const override;
};

[[nodiscard]] std::error_code make_error_code(codes e) noexcept;

} // namespace processing_pipeline_error

[[nodiscard]] std::error_category& processing_pipeline_error_category() noexcept;

} // namespace drm

template<>
struct std::is_error_code_enum<drm::processing_pipeline_error::codes> : public std::true_type {};
