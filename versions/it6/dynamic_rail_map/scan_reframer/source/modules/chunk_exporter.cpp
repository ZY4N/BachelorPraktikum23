#include "modules/chunk_exporter.hpp"

#include "helpers/transform_conversion.hpp"
#include "util/logger.hpp"

#include <cerrno>
#include <cmath>
#include <fstream>
#include <thread>

//--------------[ declarations ]--------------//

std::error_code drm::chunk_exporter::write_points_to_removert_file(
	const std::filesystem::path& directory, tcb::span<const types::translation_t> points, std::size_t frame_index
) noexcept {
	static constexpr auto padding_size = 6;

	auto filename_builder = std::stringstream();
	filename_builder << std::setfill('0') << std::setw(padding_size) << frame_index << ".bin";

	auto output = std::ofstream(directory / filename_builder.str());

	if (not output.good()) {
		return { errno, std::system_category() };
	}
	const auto write_component = [&output](const double& value) {
		const auto dst_value = static_cast<float>(value);
		std::array<char, sizeof(dst_value)> bytes;
		// The use of std::memcpy is unavoidable in this case because
		// std::copy does not allow for different types and reinterpret_cast leads to UB.
		std::memcpy(bytes.data(), &dst_value, bytes.size());
		output.write(bytes.data(), bytes.size());
	};

	for (const auto& point : points) {
		write_component(point.x());
		write_component(point.y());
		write_component(point.z());
		write_component(1.0);
	}

	if (not output.good()) {
		return { errno, std::system_category() };
	}

	return {};
}

std::error_code drm::chunk_exporter::write_pose_to_removert_file(
	const std::filesystem::path& directory, const drm::types::transform_t& pose
) noexcept {
	const auto matrix = drm::matrix_from(pose).matrix();
	auto output = std::ofstream(directory / "pose.txt", std::ios_base::app);
	if (not output.good()) {
		return { errno, std::system_category() };
	}
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < matrix.cols(); ++col) {
			output << matrix.coeff(row, col) << " ";
		}
	}
	output << '\n';

	if (not output.good()) {
		return { errno, std::system_category() };
	}

	return {};
}

std::size_t drm::chunk_exporter::get_number_of_prev_frames(const std::filesystem::path& directory) noexcept {
	std::size_t counter = 0;
	std::ifstream input(directory / "pose.txt");
	std::string drain;
	while (std::getline(input, drain)) {
		++counter;
	}
	return counter;
}
