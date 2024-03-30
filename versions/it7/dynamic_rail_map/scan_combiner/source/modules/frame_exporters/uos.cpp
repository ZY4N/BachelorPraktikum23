#include "modules/frame_exporters/uos.hpp"

#include "helpers/transform_conversion.hpp"
#include "util/logger.hpp"

#include <cerrno>
#include <fstream>

namespace drm::frame_exporters {

std::error_code uos::write(
	const std::filesystem::path& chunk_directory,
	std::mutex& chunk_lock,
	std::size_t frame_index,
	const drm::types::transform_t& pose,
	tcb::span<const types::translation_t> points
) noexcept {
	// Chunks can be unlocked becasue uos poses and frames are stored in unique files.
	chunk_lock.unlock();

	const auto base_filename = create_base_filename(chunk_directory / frame_folder_name, frame_index);

	auto error = std::error_code{};
	if ((error = write_pose(base_filename, pose))) {
		return error;
	}

	if ((error = write_points(base_filename, points))) {
		return error;
	}

	return error;
}

std::filesystem::path uos::create_base_filename(
	const std::filesystem::path& directory, const std::size_t frame_index
) noexcept {
	static constexpr auto padding_size = 3;
	auto filename_builder = std::stringstream();
	filename_builder << "scan" << std::setfill('0') << std::setw(padding_size) << frame_index;
	return directory / filename_builder.str();
}

std::error_code uos::write_pose(
	const std::filesystem::path& base_filename, const drm::types::transform_t& pose
) noexcept {

	auto pose_filename = base_filename;
	pose_filename.replace_extension(".pose");
	auto out = std::ofstream(pose_filename);

	if (not out) {
		return { errno, std::system_category() };
	}

	out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
	out << pose.translation.x() << ' ' << pose.translation.y() << ' ' << pose.translation.z() << '\n';

	double angle_x, angle_y, angle_z;
	extractEulerAngleXYZ(matrix_from(pose), angle_x, angle_y, angle_z);

	static constexpr auto to_degrees = 180.0 / M_PI;
	out << to_degrees * angle_x << " " <<  to_degrees * angle_y << " " << to_degrees * angle_z << '\n';

	if (not out) {
		return { errno, std::system_category() };
	}

	return {};
}

std::error_code uos::write_points(
	const std::filesystem::path& base_filename, tcb::span<const types::translation_t> points
) noexcept {

	auto points_filename = base_filename;
	points_filename.replace_extension(".3d");
	auto out = std::ofstream(points_filename);

	if (not out) {
		return { errno, std::system_category() };
	}

	for (const auto& point : points) {
		out << std::hexfloat << point.x() << " " << std::hexfloat << point.y() << " " << std::hexfloat << point.z()
			<< "\n";
	}

	if (not out) {
		return { errno, std::system_category() };
	}

	return {};
}

} // namespace drm::frame_exporters
