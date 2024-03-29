#include "converter.hpp"

#include "util/logger.hpp"

#include <array>
#include <charconv>
#include <fstream>
#include <pcl/io/pcd_io.h>

namespace kitti2pcd_internal {

std::error_code convert_chunk(point_cloud_t& chunk_cloud, point_cloud_t& frame_cloud, const std::filesystem::path& chunk_path) {

	auto error = std::error_code{};

	auto poses = std::vector<transform_t>{};
	if ((error = read_kitti_pose_file(chunk_path / "pose.txt", poses))) {
		return error;
	}

	for (const auto& file : std::filesystem::directory_iterator{ chunk_path / "frames" }) {

		auto file_path = file.path();
		if (!(file_path.extension() == ".bin")) {
			continue;
		}

		if ((error = read_kitti_point_file(file_path, frame_cloud))) {
			return error;
		}

		frame_cloud.resize(frame_cloud.size());
		frame_cloud.is_dense = false;

		file_path.replace_extension(".pcd");
		try {
			pcl::io::savePCDFileBinary(file_path, frame_cloud);
		} catch (const std::exception& e) {
			logger::error("Error while writing frame points to %: %", file_path, e.what());
			return std::make_error_code(std::errc::io_error);
		}

		std::size_t pose_index;
		auto filename_only = file_path.filename().string();
		if ((error = frame_id_from_filename(filename_only, pose_index))) {
			logger::error("Cannot extract frame id from %: %", file_path, error.message());
			continue;
		}

		if (pose_index >= poses.size()) {
			logger::error("Invalid pose index % out of %.", pose_index, poses.size());
			continue;
		}

		transform_cloud(frame_cloud, poses[pose_index]);

		chunk_cloud += frame_cloud;
		frame_cloud.clear();
	}

	chunk_cloud.resize(chunk_cloud.size());
	chunk_cloud.is_dense = false;

	const auto combined_path = chunk_path / "combined.pcd";
	try {
		pcl::io::savePCDFileBinary(combined_path, chunk_cloud);
	} catch (const std::exception& e) {
		logger::error("Error while writing combined frame points to %: %", combined_path, e.what());
		return std::make_error_code(std::errc::io_error);
	}

	return {};
}

std::error_code read_kitti_point_file(const std::filesystem::path& bin_path, point_cloud_t& cloud) {
	auto in = std::ifstream(bin_path);
	if (not in.is_open()) {
		return std::make_error_code(static_cast<std::errc>(errno));
	}

	using component_t = float;

	const auto read_component = [&in]() -> component_t {
		alignas(component_t) std::array<char, sizeof(component_t)> bytes;
		in.read(bytes.data(), bytes.size());
		const auto component_ptr = reinterpret_cast<component_t*>(bytes.data());
		return *std::launder(component_ptr);
	};

	while (in.good() and not in.eof()) {
		const auto x = read_component();
		const auto y = read_component();
		const auto z = read_component();
		in.ignore(sizeof(component_t));
		cloud.emplace_back(x, y, z);
	}

	return {};
}

std::error_code read_kitti_pose_file(const std::filesystem::path& filename, std::vector<transform_t>& poses) {
	
	auto in = std::ifstream(filename);
	if (not in.is_open()) {
		return std::make_error_code(static_cast<std::errc>(errno));
	}
	
	in >> std::skipws;

	auto line = std::string{};
	auto current_pose = transform_t{};

	while (not in.eof()) {
		auto& matrix = current_pose.matrix();
		for (int row = 0; row < 3; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (not (in >> matrix.row(row)[col])) {
					return in.eof() ? std::error_code{} : std::make_error_code(std::errc::invalid_argument);
				}
			}
		}
		matrix.row(3)[3] = 1.0;
		poses.push_back(current_pose);
		in.get();
	}

	return {};
}

std::error_code frame_id_from_filename(const std::string& filename, std::size_t& id) {
	const auto result = std::from_chars(filename.cbegin().base(), filename.cend().base(), id);
	return std::make_error_code(result.ec);
}

void transform_cloud(point_cloud_t& cloud, const transform_t& pose) {
	for (auto& point : cloud) {
		auto point3D = point_t{ point.x, point.y, point.z };
		point3D = pose * point3D;
		point.x = static_cast<float>(point3D.x());
		point.y = static_cast<float>(point3D.y());
		point.z = static_cast<float>(point3D.z());
	}
}

} // namespace kitti2pcd_internal
