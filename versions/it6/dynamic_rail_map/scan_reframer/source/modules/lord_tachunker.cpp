#include "modules/lord_tachunker.hpp"

#include "helpers/transform_conversion.hpp"
#include "lidar_parsers/parse_velodyne_lidar_points.hpp"
#include "modules/chunk_exporter.hpp"
#include "modules/frame_exporter.hpp"
#include "modules/metadata.hpp"
#include "modules/reframer.hpp"
#include "modules/unbagger.hpp"
#include "util/logger.hpp"
#include "version.hpp"

#include <algorithm>
#include <sstream>

// Give me C++20 default comparison!!!
static bool operator==(const drm::types::chunk_pos_t& a, const drm::types::chunk_pos_t& b) {
	return a.x == b.x and a.y == b.y;
}

static bool operator!=(const drm::types::chunk_pos_t& a, const drm::types::chunk_pos_t& b) {
	return a.x != b.x or a.y != b.y;
}

static bool operator<(const drm::types::chunk_pos_t& a, const drm::types::chunk_pos_t& b) {

	static_assert(sizeof(drm::types::chunk_pos_t) == sizeof(std::uint64_t));
	static_assert(2 * sizeof(drm::types::chunk_coord_t) == sizeof(std::uint64_t));

	std::uint64_t num_a, num_b;
	std::memcpy(&num_a, &a, sizeof(drm::types::chunk_pos_t));
	std::memcpy(&num_b, &b, sizeof(drm::types::chunk_pos_t));

	return num_a < num_b;
}

namespace drm {

lord_tachunker::lord_tachunker(
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
) :
	m_lidar_topics_vector{ lidar_topics_vector },
	m_num_threads{ num_threads },
	m_relative_begin_time{ relative_begin_time },
	m_relative_end_time{ relative_end_time },
	m_time_per_block{ time_per_block },
	m_transform_padding{ transform_padding },
	m_chunk_size{ chunk_size },
	m_max_position_deviation{ max_position_deviation },
	m_max_scan_position_deviation{ max_scan_position_deviation },
	m_max_radial_distance{ max_radial_distance },
	m_max_peripheral_distance{ max_peripheral_distance },
	m_filter{ drm::distance_filtering::create_peripheral_filter(max_radial_distance, max_peripheral_distance) } {
	setup_segmentation_buffers();
}

void lord_tachunker::setup_segmentation_buffers() {

	const auto max_radius = std::max(m_max_radial_distance, m_max_peripheral_distance);
	const auto max_chunk_diameter = 2 * static_cast<std::uint32_t>(std::abs(std::ceil(max_radius / m_chunk_size)));
	const auto max_chunks_per_frame = max_chunk_diameter * max_chunk_diameter;

	// count = 2^(2 * order) <-> order = log2(count) / 2
	m_chunk_quad_tree_order = static_cast<std::uint32_t>(std::ceil(std::log2(max_chunks_per_frame) / 2.0));

	// Limit number of buckets.
	m_chunk_quad_tree_order = std::min(m_chunk_quad_tree_order, std::uint32_t{ 6 });

	// Calculate quad-tree bucket count from order
	const auto num_buckets = static_cast<std::uint32_t>(std::pow(2, 2 * m_chunk_quad_tree_order));

	const auto bytes_without_bucket_size = sizeof(drm::types::translation_t) * num_buckets * m_num_threads;

	logger::debug(
		"Using % buckets (order %), taking up %MB by default but can grow to %MB.",
		num_buckets,
		m_chunk_quad_tree_order,
		static_cast<double>(bytes_without_bucket_size * point_bucket_default_size) / 1000'000.0,
		static_cast<double>(bytes_without_bucket_size * point_bucket_max_size) / 1000'000.0
	);

	m_segmenting_thread_ctxs.reserve(m_num_threads);

	for (std::size_t i{}; i != m_num_threads; ++i) {
		auto& ctx = m_segmenting_thread_ctxs.emplace_back();
		ctx.chunk_buckets.resize(num_buckets);
		for (auto& bucket : ctx.chunk_buckets) {
			bucket.points.reserve(point_bucket_default_size);
		}
	}
}

std::error_code lord_tachunker::extract_and_filter(
	const std::filesystem::path& filename, const std::filesystem::path& output_path
) {

	std::cout << std::fixed << std::setprecision(4);

	std::error_code error{};
	if ((error = extractor.open(filename))) {
		logger::error("Error while opening rosbag %: %", filename, error.message());
		return error;
	}

	// if directory already exists create_directories returns false but there is no error.
	if (not std::filesystem::create_directories(output_path, error) and error) {
		logger::error("Error while creating output directory %: %", output_path, error.message());
		return error;
	}

	chunk_pos_lookup.clear();
	chunk_meta_entries.clear();

	const drm::metadata::reframer_parameters_t parameters{ m_lidar_topics_vector,         m_relative_begin_time,
		                                                   m_relative_end_time,           m_max_position_deviation,
		                                                   m_max_scan_position_deviation, m_max_radial_distance,
		                                                   m_max_peripheral_distance };
	const drm::metadata::reframer_config_t config(drm::metadata::get_version(), parameters);

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

		std::vector<drm::types::timed_transform_t> transforms;
		std::vector<drm::types::timed_velocity_t> velocities;
		// std::vector<drm::types::timed_rotation_t> rotations;
		std::vector<drm::types::timed_point_t> timed_points;
		drm::types::transform_t sensor_transform;

		if ((error = extract_data(
				 interval_begin,
				 interval_end,
				 transforms,
				 velocities,
				 // rotations,
				 timed_points,
				 sensor_transform
			 ))) {
			logger::warn("Error while extracting data: %\nSkipping block %", error.message(), block_index);
			continue;
		}

		logger::info("Processing points...");

		auto reframed_points = tcb::span{ timed_points };

		const auto min_division_size = reframed_points.size() / m_num_threads;
		const auto num_left = reframed_points.size() % m_num_threads;

		std::vector<std::thread> threads;
		for (std::size_t i{}; i != m_num_threads; ++i) {
			threads.emplace_back([&, index = i]() {
				const auto begin = index * min_division_size + std::min(index, num_left);
				const auto end = begin + min_division_size + (index < num_left);

				auto& ctx = m_segmenting_thread_ctxs[index];
				auto block_points = reframed_points.subspan(begin, std::min(end, reframed_points.size()) - begin);

				auto thread_error = process_points(
					output_path,
					ctx,
					transforms,
					velocities,
					// rotations,
					block_points,
					sensor_transform
				);
				if (thread_error) {
					logger::warn("Error in thread %: %", index, thread_error.message());
				}
			});
		}

		for (auto& thread : threads) {
			thread.join();
		}

		logger::info("Finished processing points.");

		logger::info("Writing meta data...");

		std::size_t num_chunk_entries_left = chunk_pos_lookup.size();

		// writing meta data
		threads.clear();
		for (std::size_t i{}; i != m_num_threads; ++i) {
			threads.emplace_back([&]() {
				std::stringstream chunk_name_stream{};
				std::error_code thread_error;
				while (true) {
					types::chunk_pos_t chunk_pos;
					std::size_t chunk_index;
					{
						const std::lock_guard<std::mutex> lock(chunk_pos_lookup_lock);
						if (num_chunk_entries_left == 0) {
							break;
						}
						std::tie(chunk_pos, chunk_index) = chunk_pos_lookup[--num_chunk_entries_left];
					}
					auto& [chunk_lock, chunk_meta] = chunk_meta_entries.at(chunk_index);

					if (chunk_meta.added_frames.empty()) {
						continue;
					}

					chunk_name_stream.str("");
					chunk_name_stream << "chunk" << chunk_pos.x << "_" << chunk_pos.y;
					const auto meta_json_path = output_path / chunk_name_stream.str() / "meta.json";

					auto local_config = config;
					// read
					drm::metadata::metadata_t metadata{};
					if (std::filesystem::exists(meta_json_path, thread_error) and not thread_error) {
						if ((thread_error = drm::metadata::read_meta_json_to(meta_json_path, metadata))) {
							logger::error(
								"Error while reading meta.json at % : %.",
								meta_json_path,
								thread_error.message()
							);
							continue;
						}
					}

					// append
					const auto config_index = static_cast<uint64_t>(
						drm::metadata::lookup_or_create_config_entry(metadata, local_config)
					);
					const auto rosbag_index = static_cast<uint64_t>(
						drm::metadata::lookup_or_create_rosbag_entry(metadata, filename.filename().string())
					);

					metadata.scans.emplace_back(
						config_index,
						rosbag_index,
						drm::metadata::get_current_date(),
						chunk_meta.added_frames.begin_index,
						chunk_meta.added_frames.end_index,
						chunk_meta.num_points
					);

					if ((thread_error = drm::metadata::write_meta_json(meta_json_path, metadata))) {
						logger::error(
							"Error while writing meta.json at % : %.",
							meta_json_path,
							thread_error.message()
						);
					}

					chunk_meta.added_frames.clear();
				}
			});
		}

		for (auto& thread : threads) {
			thread.join();
		}

		logger::info("Finished writing meta data.");
	}

	return error;
}

std::error_code lord_tachunker::extract_data(
	const types::timestamp_t& begin_time,
	const types::timestamp_t& end_time,
	std::vector<drm::types::timed_transform_t>& transforms,
	std::vector<drm::types::timed_velocity_t>& velocities,
	// std::vector<drm::types::timed_rotation_t>& rotations,
	std::vector<drm::types::timed_point_t>& timed_points,
	drm::types::transform_t& sensor_transform
) {
	std::error_code error;

	const auto to_minutes = [](const drm::types::timestamp_t ts) {
		using minutes_t = std::chrono::duration<double, std::ratio<60>>;
		return std::chrono::duration_cast<minutes_t>(ts).count();
	};

	logger::info("Extracting frames from %min to %min", to_minutes(begin_time), to_minutes(end_time));

	const auto padded_interval_begin = m_transform_padding < begin_time ? (begin_time - m_transform_padding)
																		: begin_time;
	const auto padded_interval_end = end_time + m_transform_padding;
	logger::info("padded frames from %min to %min", to_minutes(padded_interval_begin), to_minutes(padded_interval_end));

	logger::info("Extracting transforms...");
	if ((error = extractor.extract_transforms(
			 transforms,
			 "/tf",
			 "luisenplatz",
			 padded_interval_begin,
			 padded_interval_end,
			 m_max_position_deviation
		 ))) {
		logger::warn("Error while extracting transforms: %", error.message());
		return error;
	}
	logger::info("Extracted % transform(s)", transforms.size());

	logger::info("Extracting velocities...");
	if ((error = extractor.extract_velocities(velocities, "/odom", padded_interval_begin, padded_interval_end))) {
		logger::warn("Error while extracting velocities: %", error.message());
		return error;
	}
	logger::info("Extracted % velocities", velocities.size());

	/*logger::info("Extracting rotations...");
	std::vector<drm::types::timed_rotation_t> rotations;
	if ((error = extractor.extract_imu_data(rotations, "/sensors/piksi/imu", padded_interval_begin,
	padded_interval_end)
	    )) {
	    logger::error("Error while extracting rotations: %", error.message());
	    return error;
	}
	logger::info("Extracted % rotation(s)", rotations.size());*/

	logger::info("Extracting lidar points...");
	if ((error = extractor.extract_points_if(
			 m_lidar_topics_vector.at(0),
			 timed_points,
			 sensor_transform,
			 begin_time,
			 end_time,
			 drm::lidar_parsers::parse_velodyne_lidar_points<filter_t>,
			 m_filter
		 ))) {
		logger::warn("Error while extracting points: %", error.message());
		return error;
	}

	logger::info("Extracted % lidar point(s)", timed_points.size());

	return error;
}

std::error_code lord_tachunker::process_points(
	const std::filesystem::path& output_path,
	segmenting_thread_ctx& ctx,
	tcb::span<const types::timed_transform_t> transforms,
	tcb::span<const types::timed_velocity_t> velocities,
	// tcb::span<const types::timed_rotation_t> rotation,
	tcb::span<types::timed_point_t> timed_points,
	const types::transform_t& sensor_transform
) {
	std::error_code error;

	ctx.frames.clear();

	if ((error = drm::reframer::reframe_to_closest_scan_positions(
			 timed_points,
			 transforms,
			 velocities,
			 sensor_transform,
			 m_max_scan_position_deviation,
			 ctx.frames
		 ))) {
		logger::warn("Error while reframing: %", error.message());
		return error;
	}

	static constexpr auto coord_max = std::numeric_limits<types::chunk_coord_t>::max();
	static constexpr auto invalid_chunk_pos = types::chunk_pos_t{ coord_max, coord_max };

	const auto calc_chunk_position = [chunk_size = m_chunk_size](const types::translation_t& position) {
		const auto coord_to_index = [chunk_size](const double& comp) {
			return static_cast<types::chunk_coord_t>(std::floor(comp / chunk_size));
		};
		return types::chunk_pos_t{ coord_to_index(position.x()), coord_to_index(position.y()) };
	};

	// Simple spacial hash, that efficiently distributes adjacent chunks over the available buckets.
	const auto calc_spacial_hash = [quad_tree_order = m_chunk_quad_tree_order](const types::chunk_pos_t& pos) {
		using hash_t = std::uint32_t;
		static const auto hash_mask = std::numeric_limits<hash_t>::max() >> (8 * sizeof(hash_t) - quad_tree_order);

		const auto x_comp = static_cast<hash_t>(pos.x) & hash_mask;
		const auto y_comp = static_cast<hash_t>(pos.y) & hash_mask;

		return (x_comp << quad_tree_order) | y_comp;
	};

	for (const auto& frame : ctx.frames) {

		// Reset buffers
		for (auto& bucket : ctx.chunk_buckets) {
			bucket.points.clear();

			// In case some buckets get too big we reduce their capacity back to the default size.
			if (bucket.points.capacity() > point_bucket_max_size) {
				std::vector<types::translation_t> new_point_vec;
				new_point_vec.reserve(point_bucket_default_size);
				bucket.points.swap(new_point_vec);
			}

			bucket.prev_chunk_pos = invalid_chunk_pos;
			bucket.num_chunks = 0;
		}
		ctx.frame_segments.clear();

		// Sort points into chunks and chunks into buckets.
		for (const auto& point : frame.points) {
			const auto chunk_pos = calc_chunk_position(point.position);
			const auto bucket_index = calc_spacial_hash(chunk_pos);

			auto& [points, prev_chunk_pos, num_chunks] = ctx.chunk_buckets[bucket_index];
			points.push_back(point.position);

			// Saturate-add to counter.
			num_chunks += chunk_pos != prev_chunk_pos;
			num_chunks = num_chunks == 3 ? 2 : num_chunks;
			prev_chunk_pos = chunk_pos;
		}

		const auto sensor_to_dst_space = drm::matrix_from(frame.pose);
		const auto dst_to_sensor_space = sensor_to_dst_space.inverse();

		ctx.frame_segments.reserve(ctx.chunk_buckets.size());
		for (auto& bucket : ctx.chunk_buckets) {
			assert(bucket.points.empty() == (bucket.num_chunks == 0));

			if (bucket.num_chunks == 1) { // most likely case
				ctx.frame_segments.emplace_back(bucket.prev_chunk_pos, bucket.points);
			} else if (bucket.num_chunks > 1) { // very unlikely
				// Sorting can get expensive for larger ranges, so this code only runs
				// if one frame is in more than `num_buckets` chunks or weirdly malformed.
				// In this case the number of points is hopefully small enough
				// to not cause time-complexity issues.
				std::sort(
					bucket.points.begin(),
					bucket.points.end(),
					[&calc_chunk_position](const types::translation_t& a, const types::translation_t& b) {
						return calc_chunk_position(a) < calc_chunk_position(b);
					}
				);

				auto segment_begin = bucket.points.cbegin();
				auto segment_end = segment_begin;
				auto prev_pos = calc_chunk_position(bucket.points.front());

				// Find consecutive ranges of chunk points.
				for (const auto& point : bucket.points) {
					const auto chunk_pos = calc_chunk_position(point);
					if (chunk_pos != prev_pos) {						
						ctx.frame_segments.emplace_back(
							prev_pos,
							tcb::span{ segment_begin.base(), segment_end.base() }
						);
						prev_pos = chunk_pos;
						segment_begin = segment_end;
					}
					++segment_end;
				}
				if (segment_begin != bucket.points.end()) {
					const auto chunk_pos = calc_chunk_position(*segment_begin);
					ctx.frame_segments.emplace_back(chunk_pos, tcb::span{ segment_begin.base(), segment_end.base() });
				}
			}
			for (auto& point : bucket.points) {
				point = dst_to_sensor_space * point;
			}
		}

		for (const auto& [chunk_pos, chunk_points] : ctx.frame_segments) {
			std::stringstream chunk_name_stream{};
			chunk_name_stream << "chunk" << chunk_pos.x << "_" << chunk_pos.y;
			auto chunk_path = output_path / chunk_name_stream.str();

			chunk_pos_lookup_lock.lock();
			const auto lookup_it = std::upper_bound(
				chunk_pos_lookup.begin(),
				chunk_pos_lookup.end(),
				chunk_pos,
				[](const drm::types::chunk_pos_t& a, const std::pair<drm::types::chunk_pos_t, std::size_t>& b) {
					return a < b.first;
				}
			);

			std::size_t chunk_entry_index;
			if (lookup_it != chunk_pos_lookup.begin() and (lookup_it - 1)->first == chunk_pos) {
				chunk_entry_index = (lookup_it - 1)->second;
				chunk_pos_lookup_lock.unlock();
				auto& [chunk_lock, chunk_meta] = chunk_meta_entries[chunk_entry_index];
				chunk_lock.lock();
			} else {
				chunk_entry_index = chunk_meta_entries.size();
				auto& [chunk_lock, chunk_meta] = chunk_meta_entries.emplace_back(
					std::piecewise_construct,
					std::forward_as_tuple(),
					std::forward_as_tuple(chunk_meta_entry_t{})
				);
				chunk_lock.lock();
				chunk_pos_lookup.insert(lookup_it, std::make_pair(chunk_pos, chunk_entry_index));
				chunk_pos_lookup_lock.unlock();

				std::error_code fs_error;
				if (std::filesystem::exists(chunk_path, fs_error) and not fs_error) {
					const auto meta_json_path = chunk_path / "meta.json";
					if (std::filesystem::exists(meta_json_path, fs_error) and not fs_error) {
						auto& [frames_begin, frames_end] = chunk_meta.added_frames;
						drm::metadata::metadata_t meta{};
						fs_error = drm::metadata::read_meta_json_to(meta_json_path, meta);
						if (fs_error) {
							logger::warn("Error while reading meta.json at % : %.", meta_json_path, fs_error.message());
							chunk_lock.unlock();
							continue;
						}
						frames_begin = frames_end = drm::metadata::get_max_frame_id(meta);
					} else if (fs_error) {
						logger::warn(
							"Error while checking if meta file % exists: %. Assuming file does not exist.",
							meta_json_path,
							fs_error.message()
						);
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
						continue;
					}
				}

				const auto frames_path = chunk_path / "frames";
				if (not std::filesystem::create_directories(frames_path, fs_error) and fs_error) {
					logger::error(
						"Error while creating frames directory %: %. Points that belong to this chunk "
						"cannot be exported.",
						frames_path,
						fs_error.message()
					);
					chunk_lock.unlock();
					continue;
				}
			}

			auto& [chunk_lock, chunk_meta] = chunk_meta_entries[chunk_entry_index];

			chunk_meta.num_points += chunk_points.size();
			const auto frame_index = chunk_meta.added_frames.extend();

			// Add pose to pose file.
			if ((error = chunk_exporter::write_pose_to_removert_file(chunk_path, frame.pose))) {
				logger::error("Error while updating pose file %", error.message());
				chunk_lock.unlock();
				continue;
			}
			chunk_lock.unlock();

			// Write points to frame frame_index.bin file.
			if ((error = chunk_exporter::write_points_to_removert_file(
					 chunk_path / "frames",
					 chunk_points,
					 frame_index
				 ))) {
				logger::error(
					"Error while exporting frame %: %. !!!THIS SHOULD NEVER HAPPEN, YOUR DATA IS NOW CORRUPTED!!!",
					frame_index,
					error.message()
				);
			}
		}
	}

	return error;
}

} // namespace drm
