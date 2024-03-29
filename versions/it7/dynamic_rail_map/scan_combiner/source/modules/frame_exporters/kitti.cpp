
#include "modules/frame_exporters/kitti.hpp"

#include "helpers/transform_conversion.hpp"
#include "util/logger.hpp"

#include <cerrno>
#include <fstream>

namespace drm::frame_exporters {

std::error_code kitti::write(
	const std::filesystem::path& chunk_directory,
	std::mutex& chunk_lock,
	std::size_t frame_index,
	const drm::types::transform_t& pose,
	tcb::span<const types::translation_t> points
) noexcept {

	auto error = std::error_code{};

	// Add pose to pose file.
	if ((error = write_pose(chunk_directory, pose))) {
		logger::error("Error while updating pose file %", error.message());
		chunk_lock.unlock();
		return error;
	}

	chunk_lock.unlock();

	// Write points to frame 'frames/<frame_index>.bin' file.
	if ((error = write_points(chunk_directory / frame_folder_name, points, frame_index))) {
		logger::error("Error while exporting frame %: %.", frame_index, error.message());
	}

	return error;
}

std::error_code kitti::write_pose(
	const std::filesystem::path& directory, const drm::types::transform_t& pose
) noexcept {

	auto out = std::ofstream(directory / pose_filename, std::ios_base::app);
	if (not out) {
		return { errno, std::system_category() };
	}

	const auto matrix = drm::matrix_from(pose).matrix();

	out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < matrix.cols(); ++col) {
			out << matrix.coeff(row, col) << " ";
		}
	}
	out << '\n';

	if (not out) {
		return { errno, std::system_category() };
	}

	return {};
}

std::error_code kitti::write_points(
	const std::filesystem::path& directory, tcb::span<const types::translation_t> points, std::size_t frame_index
) noexcept {
	static constexpr auto padding_size = 6;

	auto filename_builder = std::stringstream();
	filename_builder << std::setfill('0') << std::setw(padding_size) << frame_index << ".bin";

	auto out = std::ofstream(directory / filename_builder.str());

	if (not out) {
		return { errno, std::system_category() };
	}
	const auto write_component = [&out](const double& value) {
		const auto dst_value = static_cast<float>(value);
		std::array<char, sizeof(dst_value)> bytes;
		// The use of std::memcpy is unavoidable in this case because
		// std::copy does not allow for different types and reinterpret_cast leads to UB.
		std::memcpy(bytes.data(), &dst_value, bytes.size());
		out.write(bytes.data(), bytes.size());
	};

	for (const auto& point : points) {
		write_component(point.x());
		write_component(point.y());
		write_component(point.z());
		write_component(1.0);
	}

	if (not out) {
		return { errno, std::system_category() };
	}

	return {};
}

} // namespace drm::frame_exporters
