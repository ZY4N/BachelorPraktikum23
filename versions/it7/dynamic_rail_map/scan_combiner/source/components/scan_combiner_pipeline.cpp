#include "components/scan_combiner_pipeline.hpp"

#include "components/reframer.hpp"
#include "components/unbagger.hpp"
#include "util/balanced_segments.hpp"
#include "util/fixed_segments.hpp"
#include "util/logger.hpp"

#include <algorithm>
#include <sstream>

namespace drm {

scan_combiner_pipeline::segmenting_thread_ctx::segmenting_thread_ctx(const std::uint32_t quad_tree_order) :
	lord_tachunker{ quad_tree_order } {
}

scan_combiner_pipeline::scan_combiner_pipeline(
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
) :
	m_point_processing_thread_multiplier{ point_processing_thread_multiplier },
	m_num_point_extraction_threads{ num_point_extraction_threads },
	m_num_transform_extraction_threads{ num_transform_extraction_threads },
	m_num_velocity_extraction_threads{ num_velocity_extraction_threads },
	m_metadata_io_threads{ metadata_io_threads },
	m_lidar_topic{ std::move(lidar_topic) },
	m_lidar_sensor_type{ sensor_type },
	m_frame_format{ frame_format },
	m_metadata_format{ metadata_format },
	m_relative_begin_time{ relative_begin_time },
	m_relative_end_time{ relative_end_time },
	m_time_per_block{ time_per_block },
	m_transform_padding{ transform_padding },
	m_chunk_size{ chunk_size },
	m_origin_ignore_radius{ origin_ignore_radius },
	m_max_scan_position_deviation{ max_scan_position_deviation },
	m_max_radial_distance{ max_radial_distance },
	m_max_peripheral_distance{ max_peripheral_distance },
	m_filter{ drm::distance_filtering::create_peripheral_filter(max_radial_distance, max_peripheral_distance) },
	m_double_point_buffers(num_point_extraction_threads),
	m_double_transform_buffers(num_transform_extraction_threads),
	m_double_velocity_buffers(num_velocity_extraction_threads) {

	const auto num_point_processing_threads = m_num_point_extraction_threads * m_point_processing_thread_multiplier;
	logger::debug(
		"Using % threads for point loading, % for transform loading, % for velocity loading, % processing threads and "
		"% "
		"metadata io threads.",
		m_num_point_extraction_threads,
		m_num_transform_extraction_threads,
		m_num_velocity_extraction_threads,
		m_num_point_extraction_threads * m_point_processing_thread_multiplier,
		m_metadata_io_threads
	);

	// Approximate number of chunks per frame.
	const auto max_radius = m_max_radial_distance;
	const auto max_chunk_diameter = 2 * static_cast<std::uint32_t>(std::abs(std::ceil(max_radius / m_chunk_size)));
	const auto max_chunks_per_frame = max_chunk_diameter * max_chunk_diameter;

	// count = 2^(2 * order) <-> order = log2(count) / 2
	auto bucket_quad_tree_order = static_cast<std::uint32_t>(std::ceil(std::log2(max_chunks_per_frame) / 2.0));

	// Limit number of buckets.
	bucket_quad_tree_order = std::min(bucket_quad_tree_order, std::uint32_t{ 5 });
	logger::debug("Using a chunk bucket quad tree order of %.", bucket_quad_tree_order);

	m_segmenting_thread_ctxs.reserve(num_point_processing_threads);
	for (std::size_t i{}; i != num_point_processing_threads; ++i) {
		m_segmenting_thread_ctxs.emplace_back(bucket_quad_tree_order);
	}
}

std::error_code scan_combiner_pipeline::scan_combiner_pipeline::process_rosbags(
	tcb::span<const std::filesystem::path> filenames, const std::filesystem::path& output_path
) noexcept {
	auto error = std::error_code{};

	// Create output directory.
	if (not std::filesystem::create_directories(output_path, error) and error) {
		return error;
	}

	// The output directory may have changed, so caches have been invalidated.
	m_chunk_pos_lookup.clear();
	m_chunk_meta_entries.clear();

	// Set readable floating point format for both output streams.
	auto& logger_ctx = logger::global_context();
	(*logger_ctx.out) << std::fixed << std::setprecision(4);
	(*logger_ctx.err) << std::fixed << std::setprecision(4);

	const auto meta_config = metadata::scan_combiner_config_t{ drm::metadata::get_version(),
		                                                       { m_lidar_topic,
		                                                         m_relative_begin_time,
		                                                         m_relative_end_time,
		                                                         m_origin_ignore_radius,
		                                                         m_max_scan_position_deviation,
		                                                         m_max_radial_distance,
		                                                         m_max_peripheral_distance } };

	// Start extraction and processing threads.

	logger::info("Initializing threads");

	const auto num_extractors =
		(m_num_point_extraction_threads + m_num_transform_extraction_threads + m_num_velocity_extraction_threads);

	std::vector<std::thread> extractors;
	extractors.reserve(num_extractors);

	// Use barrier so every thread can acquire its initial buffer
	// without running into race conditions.
	barrier buffer_barrier(num_extractors + 1);

	const auto build_extractor_logger_cfg = [](std::string_view name, std::size_t index) {
		auto extractor_cfg = logger::global_config();
		extractor_cfg.identifier = name;
		extractor_cfg.identifier += ':';
		extractor_cfg.identifier += std::to_string(index);
		extractor_cfg.flags &= ~logger::flag::thread_id;
		extractor_cfg.flags &= ~logger::flag::filename;
		extractor_cfg.flags &= ~logger::flag::line_number;
		return extractor_cfg;
	};

	for (std::size_t i{}; i != m_num_point_extraction_threads; ++i) {
		extractors.emplace_back([&, thread_index = i]() {
			extract_all_point_blocks(
				build_extractor_logger_cfg("points", thread_index),
				filenames,
				buffer_barrier,
				thread_index
			);
		});
	}

	assert(m_double_transform_buffers.size() == m_num_transform_extraction_threads);
	for (std::size_t i{}; i != m_num_transform_extraction_threads; ++i) {
		extractors.emplace_back([&, thread_index = i]() {
			extract_all_transform_blocks(
				build_extractor_logger_cfg("transforms", thread_index),
				filenames,
				buffer_barrier,
				thread_index
			);
		});
	}

	assert(m_double_velocity_buffers.size() == m_num_velocity_extraction_threads);
	for (std::size_t i{}; i != m_num_velocity_extraction_threads; ++i) {
		extractors.emplace_back([&, thread_index = i]() {
			extract_all_velocity_blocks(
				build_extractor_logger_cfg("velocities", thread_index),
				filenames,
				buffer_barrier,
				thread_index
			);
		});
	}

	// Process the blocks in the main thread.
	error = process_all_blocks(meta_config, output_path, buffer_barrier);

	// Wait for the extraction threads to terminate.
	for (auto& extractor : extractors) {
		extractor.join();
	}

	return error;
}

template<class BufferType, class F>
void scan_combiner_pipeline::extract_all_blocks(
	const logger::config& cfg,
	tcb::span<const std::filesystem::path> filenames,
	pipeline_buffer<BufferType, 2>& double_buffer,
	barrier& buffer_barrier,
	F&& extractor
) noexcept {
	using double_buffer_t = pipeline_buffer<BufferType, 2>;
	using processing_pipeline_error::codes;
	using processing_pipeline_error::make_error_code;

	unbagger bag;
	auto buffer_index = extraction_buffer_index_init;
	BufferType* buffer_ptr{ nullptr };

	const auto acquire = [&]() {
		if (not buffer_ptr) {
			buffer_index = double_buffer_t::input_buffer(buffer_index);
			buffer_ptr = &double_buffer.acquire(buffer_index);
		}
	};

	const auto release = [&]() {
		if (buffer_ptr) {
			double_buffer.release(buffer_index);
		}
		buffer_ptr = nullptr;
	};

	acquire();

	buffer_barrier.arrive_and_wait();

	for (const auto& filename : filenames) {

		logger::debug(cfg, "Opening rosbag: %", filename);

		const auto open_error = bag.open(filename);

		if (open_error) {
			logger::error(cfg, "Error while opening rosbag %: %", filename, open_error.message());

			// Propagate error to processing thread.
			// (The mechanism is equivalent to an error in the first time segment.)
			acquire();
			buffer_ptr->error = open_error;
			release();

			// Receive and ignore (own) error.
			// (An error coming from another thread
			// would only lead to the same conclusion:
			// Skip the bag and open new bag without previous error.)
			acquire();
			buffer_ptr->error = std::error_code{};

			// Skip the bag.
			continue;
		}

		const auto [begin_time, end_time] = get_to_be_processed_interval(bag);

		// Creating rosbag metadata instance for later use in write_meta_data_block
		const metadata::rosbag_metadata_t rosbag_metadata = {
			filename.filename().string(),
			std::chrono::duration_cast<types::timestamp_milli_t>(begin_time),
			std::chrono::duration_cast<types::timestamp_milli_t>(end_time)

		};

		for (const auto& [segment_begin, segment_end] : fixed_segments(begin_time, end_time, m_time_per_block)) {

			acquire();

			// Skip rest of bag if processing thread signals error
			if (buffer_ptr->error) {
				assert(buffer_ptr->error.category() == processing_pipeline_error_category());

				const auto error_type = static_cast<codes>(buffer_ptr->error.value());

				// Reset error to not trigger twice.
				buffer_ptr->error = std::error_code{};

				// 'skip_block' can be ignored, because in every case the block in question
				// has already been extracted.
				if (error_type == codes::skip_bag) {
					logger::debug(cfg, "Skipping bag %.", filename);
					// Skip rest of bag.
					break;
				} else if (error_type == codes::skip_all) {
					release();
					logger::debug(cfg, "Terminating.");
					return;
				}
			}

			extractor(rosbag_metadata, bag, segment_begin, segment_end, begin_time, end_time, *buffer_ptr);

			release();
		}
	}

	acquire();
	buffer_ptr->error = make_error_code(codes::no_more_data_left);
	release();
}

void scan_combiner_pipeline::extract_all_point_blocks(
	const logger::config cfg,
	tcb::span<const std::filesystem::path> filenames,
	barrier& buffer_barrier,
	std::size_t thread_index
) noexcept {
	extract_all_blocks(
		cfg,
		filenames,
		m_double_point_buffers[thread_index],
		buffer_barrier,
		[&](const metadata::rosbag_metadata_t& rosbag_metadata,
	        unbagger& bag,
	        const types::timestamp_t& block_begin,
	        const types::timestamp_t& block_end,
	        const types::timestamp_t& bag_begin,
	        const types::timestamp_t&,
	        point_buffer_t& buffer) {
			auto& [timed_points, sensor_transform, rosbag_metadata_buf, error] = buffer;

			const auto [segment_begin, segment_end] = balanced_segments(
				block_begin,
				block_end,
				m_num_point_extraction_threads
			)[thread_index];

			rosbag_metadata_buf = rosbag_metadata;

			timed_points.clear();

			logger::debug(
				cfg,
				"Extracting slice [ %% ; %% ]",
				to_display_time(segment_begin - bag_begin),
				display_time_unit,
				to_display_time(segment_end - bag_begin),
				display_time_unit
			);
			if ((error = bag.extract_points_if<filter_t>(
					 m_lidar_topic,
					 m_lidar_sensor_type,
					 timed_points,
					 sensor_transform,
					 segment_begin,
					 segment_end,
					 m_filter
				 ))) {
				logger::warn(cfg, "Error while extracting point block: %", error.message());
			} else {
				logger::debug(cfg, "Successfully extracted % points.", timed_points.size());
			}
		}
	);
}

void scan_combiner_pipeline::extract_all_transform_blocks(
	const logger::config cfg,
	tcb::span<const std::filesystem::path> filenames,
	barrier& buffer_barrier,
	std::size_t thread_index
) noexcept {
	extract_all_blocks(
		cfg,
		filenames,
		m_double_transform_buffers[thread_index],
		buffer_barrier,
		[&](const metadata::rosbag_metadata_t&,
	        unbagger& bag,
	        const types::timestamp_t& block_begin,
	        const types::timestamp_t& block_end,
	        const types::timestamp_t& bag_begin,
	        const types::timestamp_t& bag_end,
	        transform_buffer_t& buffer) {
			const auto [padded_block_begin, padded_block_end] = pad_spline_interval(
				block_begin,
				block_end,
				bag_begin,
				bag_end
			);
			const auto [segment_begin, segment_end] = balanced_segments(
				padded_block_begin,
				padded_block_end,
				m_num_transform_extraction_threads
			)[thread_index];

			auto& [timed_transforms, error] = buffer;

			logger::debug(
				cfg,
				"Extracting slice [ %% ; %% ]",
				to_display_time(segment_begin - bag_begin),
				display_time_unit,
				to_display_time(segment_end - bag_begin),
				display_time_unit
			);
			if ((error = bag.extract_transforms(
					 timed_transforms,
					 "/tf",
					 "luisenplatz",
					 segment_begin,
					 segment_end,
					 m_origin_ignore_radius
				 ))) {
				logger::warn(cfg, "Error while extracting transform block: %", error.message());
			} else {
				logger::debug(cfg, "Successfully extracted % transforms.", timed_transforms.size());
			}
		}
	);
}

void scan_combiner_pipeline::extract_all_velocity_blocks(
	const logger::config cfg,
	tcb::span<const std::filesystem::path> filenames,
	barrier& buffer_barrier,
	std::size_t thread_index
) noexcept {
	extract_all_blocks(
		cfg,
		filenames,
		m_double_velocity_buffers[thread_index],
		buffer_barrier,
		[&](const metadata::rosbag_metadata_t&,
	        unbagger& bag,
	        const types::timestamp_t& block_begin,
	        const types::timestamp_t& block_end,
	        const types::timestamp_t& bag_begin,
	        const types::timestamp_t& bag_end,
	        velocity_buffer_t& buffer) {
			const auto [padded_block_begin, padded_block_end] = pad_spline_interval(
				block_begin,
				block_end,
				bag_begin,
				bag_end
			);
			const auto [segment_begin, segment_end] = balanced_segments(
				padded_block_begin,
				padded_block_end,
				m_num_velocity_extraction_threads
			)[thread_index];

			auto& [timed_velocities, error] = buffer;

			timed_velocities.clear();

			logger::debug(
				cfg,
				"Extracting slice [ %% ; %% ]",
				to_display_time(segment_begin - bag_begin),
				display_time_unit,
				to_display_time(segment_end - bag_begin),
				display_time_unit
			);
			if ((error = bag.extract_velocities(timed_velocities, "/odom", segment_begin, segment_end))) {
				logger::warn(cfg, "Error while extracting velocity block: %", error.message());
			} else {
				logger::debug(cfg, "Successfully extracted % velocities.", timed_velocities.size());
			}
		}
	);
}

std::error_code scan_combiner_pipeline::process_all_blocks(
	const metadata::scan_combiner_config_t& meta_config,
	const std::filesystem::path& output_path,
	barrier& buffer_barrier
) noexcept {
	auto error = std::error_code{};

	auto extraction_buffer_index = extraction_buffer_index_init;
	auto processing_buffer_index = processing_buffer_index_init;

	using generic_double_buffer = pipeline_buffer<int, 2>;
	std::vector<point_buffer_t*> point_buffers(m_num_point_extraction_threads, nullptr);
	std::vector<transform_buffer_t*> transform_buffers(m_num_transform_extraction_threads, nullptr);
	std::vector<velocity_buffer_t*> velocity_buffers(m_num_velocity_extraction_threads, nullptr);

	const auto for_each_extraction_buffer = [&](auto&& f) {
		const auto for_each_buffer = [&f](const std::string_view name, auto& double_buffers, auto& buffer_ptrs) {
			for (std::size_t i{}; i != double_buffers.size(); ++i) {
				f(name, i, double_buffers[i], buffer_ptrs[i]);
			}
		};
		for_each_buffer("point", m_double_point_buffers, point_buffers);
		for_each_buffer("transform", m_double_transform_buffers, transform_buffers);
		for_each_buffer("velocity", m_double_velocity_buffers, velocity_buffers);
	};

	const auto acquire_all_buffers = [&](std::size_t& buffer_index) {
		buffer_index = generic_double_buffer::input_buffer(buffer_index);
		for_each_extraction_buffer([&](const auto, const auto, auto& double_buffer, auto& buffer_ptr) {
			buffer_ptr = &double_buffer.acquire(buffer_index);
		});
	};

	// Lock next buffer, so extracting threads have to wait, after extracting the first block,
	// until errors have been checked and they can continue.
	acquire_all_buffers(processing_buffer_index);

	// Wait for extraction threads to acquire their buffers and start processing.
	logger::debug("Processing thread waiting for barrier");
	buffer_barrier.arrive_and_wait();

	// Create buffers for combining extracted data from multiple threads.
	// (Combining the points would use too much memory, so those slices are processed separately)
	std::vector<drm::types::timed_transform_t> combined_timed_transforms;
	std::vector<drm::types::timed_velocity_t> combined_timed_velocities;

	for (bool keep_running = true; keep_running;) {

		// Wait for extracting threads to extract a block.
		acquire_all_buffers(extraction_buffer_index);

		logger::info("All information gathered from extraction threads.");

		// Check if error(s) occurred while extracting.
		error = std::error_code{};
		auto most_severe_outgoing_error = std::error_code{};
		auto error_thread_name = std::string_view{};
		auto error_thread_index = std::size_t{};

		const auto check_thread_error = [&](const std::error_code& thread_error,
		                                    std::string_view thread_name,
		                                    std::size_t thread_index) {
			if (not thread_error) {
				return;
			}

			using processing_pipeline_error::codes;
			using processing_pipeline_error::make_error_code;

			const auto code = thread_error.value();
			const auto& category = thread_error.category();

			std::error_code outgoing_error;

			if (category == processing_pipeline_error_category() and
			    static_cast<codes>(code) == codes::no_more_data_left) {
				outgoing_error = make_error_code(codes::skip_all);
				keep_running = false;
			} else if (category == safe_rosbag_error_category() and static_cast<safe_rosbag_error::codes>(code) == safe_rosbag_error::codes::cannot_open_bag) {
				outgoing_error = make_error_code(codes::skip_bag);
			} else {
				outgoing_error = make_error_code(codes::skip_block);
			}

			if (outgoing_error.value() > most_severe_outgoing_error.value()) {
				most_severe_outgoing_error = outgoing_error;
				error = thread_error;
				error_thread_name = thread_name;
				error_thread_index = thread_index;
			}
		};

		for_each_extraction_buffer([&](const auto name, const auto index, auto&, auto& buffer_ptr) {
			check_thread_error(buffer_ptr->error, name, index);
		});

		if (most_severe_outgoing_error) {
			logger::warn(
				"Error(s) occurred in extraction threads. The most severe one in the % extraction thread %: %",
				error_thread_name,
				error_thread_index,
				error.message()
			);

			using processing_pipeline_error::codes;
			const auto code = static_cast<codes>(most_severe_outgoing_error.value());

			switch (code) {
			case codes::skip_block:
				logger::warn("Skipping block.");
				break;
			case codes::skip_bag:
				logger::warn("Skipping bag.");
				break;
			case codes::skip_all:
				logger::warn("Skipping all remaining bags.");
				break;
			default:
				break;
			}

			// Propagate errors back via double buffer.
			for_each_extraction_buffer([&](const auto, const auto, auto&, auto& buffer_ptr) {
				buffer_ptr->error = most_severe_outgoing_error;
			});
		}

		// Hand off buffers to extraction threads.
		logger::debug("Handing off next buffer to extraction threads...");
		if (keep_running) {
			// Wait for extraction threads to receive the buffer
			// to avoid race conditions with the next loop iteration.
			for_each_extraction_buffer([&](const auto, const auto, auto& double_buffer, auto&) {
				double_buffer.handoff(processing_buffer_index);
			});
		} else {
			// No waiting needed, as this is the last iteration.
			for_each_extraction_buffer([&](const auto, const auto, auto& double_buffer, auto&) {
				double_buffer.release(processing_buffer_index);
			});
		}
		logger::debug("Finished handing off next buffer to extraction threads.");

		processing_buffer_index = extraction_buffer_index;

		// If data was successfully extracted, process the block.
		if (not error) {
			logger::info("Combining extracted data...");

			const auto num_points = std::accumulate(
				point_buffers.begin(),
				point_buffers.end(),
				std::size_t{},
				[](const auto& num_points, const auto& point_buffer) {
					return num_points + point_buffer->timed_points.size();
				}
			);

			const auto num_transforms = std::accumulate(
				transform_buffers.begin(),
				transform_buffers.end(),
				std::size_t{},
				[](const auto& num_transforms, const auto& transform_buffer) {
					return num_transforms + transform_buffer->timed_transforms.size();
				}
			);

			const auto num_velocities = std::accumulate(
				velocity_buffers.begin(),
				velocity_buffers.end(),
				std::size_t{},
				[](const auto& num_velocities, const auto& velocity_buffer) {
					return num_velocities + velocity_buffer->timed_velocities.size();
				}
			);

			logger::debug(
				"Block contains % points, % transforms and % velocities.",
				num_points,
				num_transforms,
				num_velocities
			);

			const auto combine_buffers =
				[](const auto& src_buffer_ptrs, auto& dst_buffer, const auto count, auto&& extract_values) {
					dst_buffer.resize(count);
					auto dst_it = dst_buffer.begin();
					for (const auto& src_buffer_ptr : src_buffer_ptrs) {
						const auto& src_value = extract_values(*src_buffer_ptr);
						std::copy_n(src_value.begin(), src_value.size(), dst_it);
						dst_it += src_value.size();
					}
				};

			combine_buffers(transform_buffers, combined_timed_transforms, num_transforms, [](const auto& buffer) {
				return buffer.timed_transforms;
			});

			combine_buffers(velocity_buffers, combined_timed_velocities, num_velocities, [](const auto& buffer) {
				return buffer.timed_velocities;
			});

			logger::info("Finished combining extracted data.");

			process_block(
				meta_config,
				output_path,
				point_buffers[0]->rosbag_metadata,
				combined_timed_transforms,
				combined_timed_velocities,
				point_buffers
			);

			// TODO In case of fatal error the error should be written to error,
			// the extraction threads need to be terminated and the thread needs to stop.
		}
	}

	// This error is only used for interal signalling and not an acutal error.
	if (error.category() == processing_pipeline_error_category() and
	    static_cast<processing_pipeline_error::codes>(error.value()) ==
	        processing_pipeline_error::codes::no_more_data_left) {
		error = std::error_code{};
	}

	return error;
}

void scan_combiner_pipeline::process_block(
	const metadata::scan_combiner_config_t& meta_config,
	const std::filesystem::path& output_path,
	const metadata::rosbag_metadata_t& rosbag_metadata,
	tcb::span<drm::types::timed_transform_t> timed_transforms,
	tcb::span<drm::types::timed_velocity_t> timed_velocities,
	tcb::span<point_buffer_t*> point_buffers
) noexcept {
	m_chunk_pos_lookup.clear();
	m_chunk_meta_entries.clear();

	logger::info("Processing block...");

	std::vector<std::thread> threads;
	threads.reserve(m_num_point_extraction_threads * m_point_processing_thread_multiplier);

	{
		std::size_t thread_index{};
		for (const auto& point_buffer : point_buffers) {

			const auto slices = balanced_segments(
				std::size_t{},
				point_buffer->timed_points.size(),
				m_point_processing_thread_multiplier
			);

			for (const auto& [slice_begin, slice_end] : slices) {
				threads.emplace_back([&, index = thread_index, begin = slice_begin, end = slice_end]() {
					auto& ctx = m_segmenting_thread_ctxs[index];

					const auto points_slice = tcb::span(
						(point_buffer->timed_points.begin() + begin).base(),
						end - begin
					);

					auto thread_error = process_point_block_slice(
						output_path,
						ctx,
						timed_transforms,
						timed_velocities,
						points_slice,
						point_buffer->sensor_transform
					);
					if (thread_error) {
						logger::warn("Error occurred while processing block slice %: %", index, thread_error.message());
					}
				});
				++thread_index;
			}
		}

		for (auto& thread : threads) {
			thread.join();
		}
	}

	logger::info("Finished processing block.");

	logger::info("Writing meta data for block...");

	auto num_chunk_entries_left = m_chunk_pos_lookup.size();

	threads.clear();
	threads.reserve(m_metadata_io_threads);
	for (std::size_t i{}; i != m_metadata_io_threads; ++i) {
		threads.emplace_back([&]() {
			write_meta_data_block(meta_config, output_path, rosbag_metadata, num_chunk_entries_left);
		});
	}

	for (auto& thread : threads) {
		thread.join();
	}

	logger::info("Finished writing meta data for block.");
}

std::error_code scan_combiner_pipeline::process_point_block_slice(
	const std::filesystem::path& output_path,
	segmenting_thread_ctx& ctx,
	tcb::span<const types::timed_transform_t> timed_transforms,
	tcb::span<const types::timed_velocity_t> timed_velocities,
	tcb::span<types::timed_point_t> timed_points,
	const types::transform_t& sensor_transform
) noexcept {
	std::error_code error;

	// Clear all previous frames while retaining capacity.
	ctx.frames.clear();

	if ((error = drm::reframer::reframe_to_closest_scan_positions(
			 timed_points,
			 timed_transforms,
			 timed_velocities,
			 sensor_transform,
			 m_max_scan_position_deviation,
			 ctx.frames
		 ))) {
		logger::warn("Error while reframing: %", error.message());
		return error;
	}

	for (const auto& frame : ctx.frames) {

		// Clear previous frame_chunks while keeping capacity.
		ctx.frame_chunks.clear();

		// Split frame points into chunks.
		ctx.lord_tachunker.process(frame.pose, frame.points, m_chunk_size, ctx.frame_chunks);

		// Write frame chunks to disk.
		write_chunks(output_path, ctx.chunk_name_stream, frame.pose, ctx.frame_chunks);
	}

	return {};
}

static std::ostream& operator<<(std::ostream& os, const types::chunk_pos_t& pos) {
	return os << "chunk" << pos.x << "_" << pos.y;
}

void scan_combiner_pipeline::write_chunks(
	const std::filesystem::path& output_path,
	std::stringstream& chunk_name_stream,
	const types::transform_t& pose,
	tcb::span<const types::chunk_t> chunks
) noexcept {
	for (const auto& [chunk_pos, chunk_points] : chunks) {

		// create name of chunk for output directory
		chunk_name_stream.str("");
		chunk_name_stream << chunk_pos;
		auto chunk_path = output_path / chunk_name_stream.str();

		// lock thread
		m_chunk_pos_lookup_lock.lock();

		// lookup chunk_meta_entry and if it doesn't exists create one
		std::size_t chunk_entry_index;
		std::error_code chunk_meta_entry_error;
		chunk_meta_entry_error = scan_combiner_pipeline::lookup_or_create_chunk_meta_entry(
			chunk_pos,
			chunk_entry_index,
			chunk_path
		);
		if (chunk_meta_entry_error) {
			continue;
		}

		auto& [chunk_lock, chunk_meta] = m_chunk_meta_entries[chunk_entry_index];

		chunk_meta.num_points += chunk_points.size();
		const auto frame_index = chunk_meta.added_frames.extend();

		const auto exporter_error = frame_exportation::write(
			m_frame_format,
			chunk_path,
			chunk_lock,
			frame_index,
			pose,
			chunk_points
		);

		if (exporter_error) {
			logger::error(
				"Error while exporting frame %: %. !!!OUTPUT DATA COULD BE MALFORMED!!!",
				frame_index,
				exporter_error.message()
			);
		}
	}
}

std::error_code scan_combiner_pipeline::lookup_or_create_chunk_meta_entry(
	types::chunk_pos_t chunk_pos, std::size_t& chunk_entry_index, std::filesystem::path chunk_path
) noexcept {

	// search if position is already in lookup table through binary search algorithm
	const auto lookup_it = std::upper_bound(
		m_chunk_pos_lookup.begin(),
		m_chunk_pos_lookup.end(),
		chunk_pos,
		[](const drm::types::chunk_pos_t& a, const std::pair<drm::types::chunk_pos_t, std::size_t>& b) {
			return a < b.first;
		}
	);

	// if position is already in chunk_meta_lookup write out its index if not crate new entry
	if (lookup_it != m_chunk_pos_lookup.begin() and (lookup_it - 1)->first == chunk_pos) {
		chunk_entry_index = (lookup_it - 1)->second;
		m_chunk_pos_lookup_lock.unlock();
		auto& [chunk_lock, chunk_meta] = m_chunk_meta_entries[chunk_entry_index];
		chunk_lock.lock();
	} else {
		chunk_entry_index = m_chunk_meta_entries.size();
		auto& [chunk_lock, chunk_meta] = m_chunk_meta_entries.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(),
			std::forward_as_tuple(chunk_meta_entry_t{})
		);

		chunk_lock.lock();
		m_chunk_pos_lookup.insert(lookup_it, std::make_pair(chunk_pos, chunk_entry_index));
		m_chunk_pos_lookup_lock.unlock();

		std::error_code fs_error;
		if (std::filesystem::exists(chunk_path, fs_error) and not fs_error) {
			if (metadata_transcoding::contains_metadata(m_metadata_format, chunk_path)) {
				auto& [frames_begin, frames_end] = chunk_meta.added_frames;
				drm::metadata::metadata_t meta{};
				if ((fs_error = metadata_transcoding::read(m_metadata_format, chunk_path, meta))) {
					logger::warn("Error while reading meta data in directory %: %.", chunk_path, fs_error.message());
					chunk_lock.unlock();
					return fs_error;
				}
				frames_begin = frames_end = drm::metadata::get_max_frame_id(meta);
			}
		} else {
			if (fs_error) {
				logger::warn(
					"Error while checking if directory % exists: %. Assuming directory does not exist.",
					chunk_path,
					fs_error.message()
				);
			}
			if (not std::filesystem::create_directories(chunk_path, fs_error) and fs_error) {
				logger::error(
					"Error while creating chunk directory %: %. Points that belong to this chunk "
					"cannot be exported.",
					chunk_path,
					fs_error.message()
				);
				chunk_lock.unlock();
				return fs_error;
			}
		}

		// create directory for the frames
		const auto frames_path = chunk_path / "frames";
		if (not std::filesystem::create_directories(frames_path, fs_error) and fs_error) {
			logger::error(
				"Error while creating frames directory %: %. Points that belong to this chunk "
				"cannot be exported.",
				frames_path,
				fs_error.message()
			);
			chunk_lock.unlock();
			return fs_error;
		}
	}
	return {};
}

void scan_combiner_pipeline::write_meta_data_block(
	const metadata::scan_combiner_config_t& meta_config,
	const std::filesystem::path& output_path,
	const metadata::rosbag_metadata_t& rosbag_metadata,
	std::size_t& num_chunk_entries_left
) noexcept {
	std::error_code error;

	std::stringstream chunk_name_stream{};

	while (true) {
		// Locking and releasing of Mutex
		types::chunk_pos_t chunk_pos{};
		std::size_t chunk_index;
		{
			const std::lock_guard<std::mutex> lock(m_chunk_pos_lookup_lock);
			if (num_chunk_entries_left == 0) {
				break;
			}
			std::tie(chunk_pos, chunk_index) = m_chunk_pos_lookup[--num_chunk_entries_left];
		}
		auto& [chunk_lock, chunk_meta] = m_chunk_meta_entries.at(chunk_index);

		if (chunk_meta.added_frames.empty()) {
			continue;
		}

		// Creating Path to metadata.json
		chunk_name_stream.str("");
		chunk_name_stream << chunk_pos;
		const auto chunk_path = output_path / chunk_name_stream.str();

		// Reading metadata from file
		drm::metadata::metadata_t metadata{};
		if (drm::metadata_transcoding::contains_metadata(m_metadata_format, chunk_path)) {
			if ((error = drm::metadata_transcoding::read(m_metadata_format, chunk_path, metadata))) {
				logger::error("Error while reading metadata from directory %: %.", chunk_path, error.message());
				continue;
			}
		}

		// Appending Config data to metadata
		const auto config_index = static_cast<uint64_t>(
			drm::metadata::lookup_or_create_config_entry(metadata, meta_config)
		);

		// Appending Rosbag data to metadata
		const auto rosbag_index = static_cast<uint64_t>(
			drm::metadata::lookup_or_create_rosbag_entry(metadata, rosbag_metadata)
		);

		// Appending Scans to metadata
		metadata.scans.emplace_back(
			config_index,
			rosbag_index,
			drm::metadata::get_timestamp(),
			chunk_meta.added_frames,
			chunk_meta.num_points
		);

		// Write expanded metadata back to file.
		if ((error = drm::metadata_transcoding::write(m_metadata_format, chunk_path, metadata))) {
			logger::error("Error while writing metadata to directory %: %.", chunk_path, error.message());
		}

		chunk_meta.added_frames.clear();
	}
}

std::pair<types::timestamp_t, types::timestamp_t> scan_combiner_pipeline::get_to_be_processed_interval(
	const unbagger& bag
) noexcept {
	const auto rosbag_begin = bag.begin_tim();
	const auto rosbag_end = bag.end_tim();
	const auto rosbag_duration = rosbag_end - rosbag_begin;
	return { std::min(m_relative_begin_time, rosbag_duration), std::min(m_relative_end_time, rosbag_duration) };
}

std::pair<types::timestamp_t, types::timestamp_t> scan_combiner_pipeline::pad_spline_interval(
	const types::timestamp_t& min,
	const types::timestamp_t& max,
	const types::timestamp_t& bag_min,
	const types::timestamp_t& bag_max
) noexcept {
	// Mutable for rvo
	auto padded_min = min - bag_min >= m_transform_padding ? (min - m_transform_padding) : bag_min;
	auto padded_max = bag_max - max >= m_transform_padding ? (max + m_transform_padding) : bag_max;
	return { padded_min, padded_max };
}

[[nodiscard]] typename scan_combiner_pipeline::display_time_t::rep scan_combiner_pipeline::to_display_time(
	const types::timestamp_t& ts
) {
	return std::chrono::duration_cast<display_time_t>(ts).count();
}

const char* processing_pipeline_error::category::name() const noexcept {
	return "processing_pipeline";
}

std::string processing_pipeline_error::category::message(const int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::no_more_data_left:
		return "An extraction thread extracted all data.";
	case codes::skip_block:
		return "An extraction thread needs to skip the currently opened block.";
	case codes::skip_bag:
		return "An extraction thread needs to skip the currently opened bag.";
	case codes::skip_all:
		return "An extraction thread needs to skip all remaining blocks and bags.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_code processing_pipeline_error::make_error_code(const codes e) noexcept {
	return { static_cast<int>(e), processing_pipeline_error_category() };
}

std::error_category& processing_pipeline_error_category() noexcept {
	static drm::processing_pipeline_error::category category;
	return category;
}

} // namespace drm
