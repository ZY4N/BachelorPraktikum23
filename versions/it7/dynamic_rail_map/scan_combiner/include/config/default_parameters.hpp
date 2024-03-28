#pragma once

#include "helpers/ros_time_conversion.hpp"
#include "module_interfaces/frame_exportation.hpp"
#include "module_interfaces/metadata_transcoding.hpp"
#include "module_interfaces/point_cloud_parsing.hpp"
#include "types.hpp"
#include "util/logger.hpp"

#include <chrono>
#include <thread>

namespace drm::default_parameters {

inline constexpr auto lidar_topic = "/sensors/lidar/velodyne/velodyne_points";
inline constexpr auto lidar_sensor_type = drm::point_cloud_parsing::get_sensor_type_by_name("velodyne_lidar").value();
inline constexpr auto frame_format = drm::frame_exportation::get_format_by_name("kitti").value();
inline constexpr auto metadata_format = drm::metadata_transcoding::get_format_by_name("json").value();

inline const auto num_threads = std::thread::hardware_concurrency();
inline constexpr auto log_level = logger::level::log;

inline const auto relative_begin_time = drm::ros_time_to_timestamp_t(ros::TIME_MIN);
inline const auto relative_end_time = drm::ros_time_to_timestamp_t(ros::TIME_MAX);
inline constexpr auto time_per_block = std::chrono::minutes{ 7 };
inline constexpr auto spline_time_padding = std::chrono::seconds{ 10 };

inline constexpr auto chunk_size = 30.0;
inline constexpr auto max_radial_distance = 30.0;
inline constexpr auto max_peripheral_distance = 20.0;
inline constexpr auto max_scan_position_deviation = 1.0;
inline constexpr auto origin_ignore_radius = 1.0;

inline constexpr auto point_extraction_thread_portion = 0.3;
inline constexpr auto transform_extraction_thread_portion = 0.2;
inline constexpr auto velocity_extraction_thread_portion = 0.2;
inline constexpr auto metadata_io_thread_portion = 0.5;
inline constexpr auto processing_thread_multiplier = 3;

} // namespace drm::default_parameters
