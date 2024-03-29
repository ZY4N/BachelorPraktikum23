#include "util/logger.hpp"

#include <algorithm>
#include <charconv>

void kitti2pcd_internal::print_progress(const std::size_t count, const std::size_t total) {

	static constexpr auto width = std::max(12, 88);
	static constexpr auto spinner = std::string_view{ "|/-\\" };
	static constexpr auto arrow = std::string_view{ "=>" };

	static auto buffer = [&]() {
		auto buffer = std::string(width, ' ');
		auto offset = std::size_t{};
		for (const auto spacing : { 1, width - 11, 4 }) {
			buffer[offset++] = '[';
			offset += spacing;
			buffer[offset++] = ']';
		}
		buffer[width - 2] = '%';
		return buffer;
	}();

	const auto progress = std::min(static_cast<double>(count) / static_cast<double>(total), 1.0);
	const auto percent = static_cast<std::size_t>(std::round(100 * progress));
	const auto digits = (percent >= 1) + (percent >= 10) + (percent >= 100);
	const auto length = static_cast<std::size_t>(std::round((width - 12) * progress));

	buffer[1] = spinner[count % spinner.size()];
	std::fill_n(buffer.begin() + 4, length, arrow[0]);
	std::fill(buffer.begin() + 4 + length, buffer.end() - 7, ' ');
	buffer[4 + length] = arrow[1];
	std::to_chars(&buffer[width - 2 - digits], &buffer[width - 2], percent);

	std::cout << buffer << std::flush << '\r';
}

template<typename Iterator>
void kitti2pcd::convert_chunks(Iterator begin, Iterator end, std::size_t& chunk_index, std::size_t chunk_count) {
	using namespace kitti2pcd_internal;

	auto chunk_cloud = point_cloud_t{};
	auto frame_cloud = point_cloud_t{};

	for (; begin != end; ++begin) {
		const auto error = convert_chunk(chunk_cloud, frame_cloud, *begin);
		if (error) {
			logger::warn("Error while processing chunk: %", error.message());
		}
		chunk_cloud.clear();
		frame_cloud.clear();
		print_progress(++chunk_index, chunk_count);
	}
}
