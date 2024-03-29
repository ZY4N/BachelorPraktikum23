#pragma once

#include "Eigen/Geometry"

#include <filesystem>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <system_error>
#include <vector>

namespace kitti2pcd {

template<typename Iterator>
inline void convert_chunks(Iterator begin, Iterator end, std::size_t& chunk_index, std::size_t chunk_count);

} // namespace kitti2pcd

namespace kitti2pcd_internal {

using point_t = Eigen::Vector3d;
using transform_t = Eigen::Isometry3d;
using point_cloud_t = pcl::PointCloud<pcl::PointXYZ>;

[[nodiscard]] std::error_code convert_chunk(
	point_cloud_t& chunk_cloud, point_cloud_t& frame_cloud, const std::filesystem::path& chunk_path
);

[[nodiscard]] std::error_code frame_id_from_filename(const std::string& filename, std::size_t& id);
[[nodiscard]] std::error_code read_kitti_pose_file(const std::filesystem::path& filename, std::vector<transform_t>& poses);
[[nodiscard]] std::error_code read_kitti_point_file(const std::filesystem::path& bin_path, point_cloud_t& cloud);

void transform_cloud(point_cloud_t& cloud, const transform_t& pose);

inline void print_progress(std::size_t count, std::size_t total);

} // namespace kitti2pcd_internal

#include "converter.ipp"
