#include "modules/frame_exporter.hpp"

#include "helpers/transform_conversion.hpp"
#include "util/logger.hpp"

#include <cerrno>
#include <cmath>
#include <fstream>
#include <thread>

//--------------[ declarations ]--------------//

std::error_code drm::frame_exporter::write_frames_to_uos_files(
	const std::filesystem::path& directory, tcb::span<const types::lidar_frame_t> frames, int num_threads
) noexcept {
	if (not std::filesystem::exists(directory)) {
		std::filesystem::create_directories(directory);
	}
	std::error_code error{};
	std::vector<std::thread> workers;
	const auto block_size = frames.size() / num_threads;
	const auto frames_left = frames.size() % num_threads;

	for (int thread_index = 0; thread_index < num_threads; ++thread_index) {

		const auto frame_block_begin =
			(thread_index * block_size + std::min(static_cast<std::size_t>(thread_index), frames_left));

		const auto frame_block = frames.subspan(
			frame_block_begin,
			block_size + (static_cast<std::size_t>(thread_index) < frames_left)
		);
		workers.emplace_back([thread_index, &directory, frame_block, frame_block_begin]() {
			const auto error = frame_exporter_internal::write_frame_set_to_uos_file(
				directory,
				frame_block,
				frame_block_begin
			);
			if (error) {
				logger::warn("Error occurred in Thread %: %", thread_index, error.message());
			}
		});
	}
	for (auto& worker : workers) {
		worker.join();
	}

	return {};
}

std::error_code drm::frame_exporter_internal::write_frame_set_to_uos_file(
	const std::filesystem::path& directory, tcb::span<const types::lidar_frame_t> frames, std::size_t file_index
) noexcept {
	std::error_code error{};
	auto filename_builder = std::stringstream();
	static constexpr auto padding_size = 3; // 3DTK needs and only accepts three wide padding

	for (const auto& frame : frames) {
		if (frame.points.empty()) {
			logger::warn("Skipped empty frame with index %", file_index);
			continue;
		}

		filename_builder << "scan" << std::setfill('0') << std::setw(padding_size) << file_index;
		if ((error = frame_exporter_internal::write_single_frame_to_uos_file(directory / filename_builder.str(), frame)
		    )) {
			return error;
		}
		++file_index;
		// Clears the filename_builder stream
		filename_builder.str("");
	}

	return {};
}

std::error_code drm::frame_exporter_internal::write_single_frame_to_uos_file(
	const std::filesystem::path& filename, const types::lidar_frame_t& frame
) noexcept {
	std::error_code error{};

	if ((error = write_points_to_uos_file(filename, frame.points))) {
		return error;
	}
	if ((error = write_pose_to_uos_file(filename, frame.pose))) {
		return error;
	}

	return {};
}

std::error_code drm::frame_exporter_internal::write_points_to_uos_file(
	const std::filesystem::path& filename, tcb::span<const types::timed_point_t> points
) noexcept {
	auto points_filename = filename;
	points_filename += ".3d";
	auto out = std::ofstream(points_filename);

	if (not out.good()) {
		return { errno, std::system_category() };
	}

	for (const auto& point : points) {
		out << std::hexfloat << point.position.x() << " " << std::hexfloat << point.position.y() << " " << std::hexfloat
			<< point.position.z() << "\n";
	}

	if (not out.good()) {
		return { errno, std::system_category() };
	}

	return {};
}

template<typename T>
void extractEulerAngleXYZ(const drm::types::matrix_t& transform, T& t1, T& t2, T& t3) noexcept {
	const auto& M = transform.matrix();
	T T1 = std::atan2(M.col(2)[1], M.col(2)[2]);
	T C2 = std::sqrt(M.col(0)[0] * M.col(0)[0] + M.col(1)[0] * M.col(1)[0]);
	T T2 = std::atan2(-M.col(2)[0], C2);
	T S1 = std::sin(T1);
	T C1 = std::cos(T1);
	T T3 = std::atan2(S1 * M.col(0)[2] - C1 * M.col(0)[1], C1 * M.col(1)[1] - S1 * M.col(1)[2]);
	t1 = -T1;
	t2 = -T2;
	t3 = -T3;
}

std::error_code drm::frame_exporter_internal::write_pose_to_uos_file(
	const std::filesystem::path& filename, const drm::types::transform_t& pose
) noexcept {
	auto pose_filename = filename;
	pose_filename += ".pose";
	auto out = std::ofstream(pose_filename);
	if (not out.good()) {
		return { errno, std::system_category() };
	}

	out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
	out << pose.translation.x() << ' ' << pose.translation.y() << ' ' << pose.translation.z() << '\n';

	double angle_x, angle_y, angle_z;
	extractEulerAngleXYZ(matrix_from(pose), angle_x, angle_y, angle_z);

	static constexpr auto to_degrees = 180.0 / M_PI;
	out << std::hexfloat << to_degrees * angle_x << " " << std::hexfloat << to_degrees * angle_y << " " << std::hexfloat
		<< to_degrees * angle_z;

	if (not out.good()) {
		return { errno, std::system_category() };
	}

	return {};
}

std::error_code drm::frame_exporter::write_frames_to_removert_files(
	const std::filesystem::path& directory, tcb::span<const types::lidar_frame_t> frames, int num_threads
) noexcept {
	if (not std::filesystem::exists(directory)) {
		std::filesystem::create_directories(directory);
	}
	std::error_code error{};
	std::vector<std::thread> workers;
	const auto block_size = frames.size() / num_threads;
	const auto frames_left = frames.size() % num_threads;

	// Write all poses to file
	auto output = std::ofstream(directory / "pose.txt");
	for (const auto& frame : frames) {
		error = frame_exporter_internal::write_pose_to_removert_file(output, frame.pose);
		if (error) {
			logger::warn("Error occurred while writing pose file: %", error.message());
		}
	}

	// Write all points to files
	for (int thread_index = 0; thread_index < num_threads; ++thread_index) {

		const auto frame_block_begin =
			(thread_index * block_size + std::min(static_cast<std::size_t>(thread_index), frames_left));

		const auto frame_block = frames.subspan(
			frame_block_begin,
			block_size + (static_cast<std::size_t>(thread_index) < frames_left)
		);

		workers.emplace_back([thread_index, &directory, frame_block, frame_block_begin]() {
			auto file_index = frame_block_begin;
			auto filename_builder = std::stringstream();
			static constexpr auto padding_size = 6; // Check if padding is needed

			for (const auto& frame : frame_block) {
				filename_builder << std::setfill('0') << std::setw(padding_size) << file_index;

				const auto error = frame_exporter_internal::write_points_to_removert_file(
					directory / filename_builder.str(),
					frame.points
				);
				if (error) {
					logger::warn("Error occurred in Thread %: %", thread_index, error.message());
				}

				++file_index;
				// Clears the filename_builder stream
				filename_builder.str("");
			}
		});
	}
	for (auto& worker : workers) {
		worker.join();
	}

	return {};
}

std::error_code drm::frame_exporter_internal::write_points_to_removert_file(
	const std::filesystem::path& base_filename, tcb::span<const types::timed_point_t> points
) noexcept {
	auto points_filename = base_filename;
	points_filename += ".bin";
	auto output = std::ofstream(points_filename);

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
		write_component(point.position.x());
		write_component(point.position.y());
		write_component(point.position.z());
		write_component(1.0);
	}

	if (not output.good()) {
		return { errno, std::system_category() };
	}

	return {};
}

std::error_code drm::frame_exporter_internal::write_pose_to_removert_file(
	std::ofstream& output, const drm::types::transform_t& pose
) noexcept {
	if (not output.good()) {
		return { errno, std::system_category() };
	}

	const auto matrix = drm::matrix_from(pose).matrix();

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
