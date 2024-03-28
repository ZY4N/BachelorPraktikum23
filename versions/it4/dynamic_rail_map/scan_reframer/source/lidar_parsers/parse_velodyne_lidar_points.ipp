#ifndef INCLUDE_UNBAGGER_IMPLEMENTATION
#	error Never include this file directly include 'parse_velodyne_lidar_points.hpp'
#endif

#include "helpers/ros_point_field_helpers.hpp"
#include "helpers/ros_time_conversion.hpp"
#include "helpers/safe_rosbag.hpp"

#include <sensor_msgs/PointCloud2.h>

namespace drm::lidar_parsers {

const char* velodyne_lidar_point_parsing_error::category::name() const noexcept {
	return "unbagger";
}

std::string velodyne_lidar_point_parsing_error::category::message(int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::point_field_mismatch:
		return "Layout and/or data types of given lidar frame do not meet requirements.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}

std::error_category& unbagger_error_category() noexcept {
	static velodyne_lidar_point_parsing_error::category category;
	return category;
}

std::error_code velodyne_lidar_point_parsing_error::make_error_code(codes e) noexcept {
	return { static_cast<int>(e), unbagger_error_category() };
}

template<typename P>
std::error_code parse_velodyne_lidar_points(
	rosbag::View& lidar_frames_view, std::vector<types::timed_point_t>& timed_points, const P& predicate
) noexcept {
	using ec = velodyne_lidar_point_parsing_error::codes;
	using velodyne_lidar_point_parsing_error::make_error_code;
	auto error = std::error_code{};

	if (lidar_frames_view.size() == 0) {
		return error;
	}

	auto first_cloud = boost::shared_ptr<sensor_msgs::PointCloud2>{};
	if ((error = safe_rosbag::instantiate_msg_iterator<sensor_msgs::PointCloud2>(lidar_frames_view.begin(), first_cloud)
	    )) {
		return error;
	}

	static constexpr auto offset_x = 0, offset_y = 4, offset_z = 8, offset_time = 18;

	static const auto required_fields = std::array{
		make_point_field("x", offset_x, sensor_msgs::PointField::FLOAT32, 1),
		make_point_field("y", offset_y, sensor_msgs::PointField::FLOAT32, 1),
		make_point_field("z", offset_z, sensor_msgs::PointField::FLOAT32, 1),
		make_point_field("time", offset_time, sensor_msgs::PointField::FLOAT32, 1)
	};

	const auto [point_ok, point_size] = check_fields(required_fields, first_cloud->fields);

	if (not point_ok) {
		return make_error_code(ec::point_field_mismatch);
	}

	auto num_lidar_frames = std::size_t{};

	for (const auto& msg : lidar_frames_view) {

		auto lidar_frame_msg = boost::shared_ptr<sensor_msgs::PointCloud2>{};
		if ((error = safe_rosbag::instantiate_msg<sensor_msgs::PointCloud2>(msg, lidar_frame_msg))) {
			continue;
		}

		++num_lidar_frames;

		const auto& lidar_frame_data = lidar_frame_msg->data;
		const auto frame_timestamp = ros_time_to_timestamp_t(lidar_frame_msg->header.stamp);

		for (std::size_t i{}; i + point_size < lidar_frame_data.size(); i += point_size) {

			const auto point_bytes = tcb::span{ &lidar_frame_data[i], point_size };

			const auto position = types::translation_t{ read_point_field<float>(point_bytes, offset_x),
				                                        read_point_field<float>(point_bytes, offset_y),
				                                        read_point_field<float>(point_bytes, offset_z) };

			if (predicate(position)) {
				using std::chrono::duration;

				using signed_timestamp_t = duration<
					std::make_signed_t<types::timestamp_t::rep>,
					types::timestamp_t::period>;
				using seconds_timestamp_t = duration<double>;

				const auto delta_time = read_point_field<float>(point_bytes, offset_time);

				const auto timestamp = std::chrono::duration_cast<types::timestamp_t>(
					frame_timestamp + std::chrono::duration_cast<signed_timestamp_t>(seconds_timestamp_t(delta_time))
				);

				const auto reverse_dst = std::find_if(
					timed_points.rbegin(),
					timed_points.rend(),
					[&timestamp](const auto& other_point) { return timestamp >= other_point.timestamp; }
				);

				timed_points.emplace(reverse_dst.base(), position, timestamp);
			}
		}
	}

	if (num_lidar_frames != lidar_frames_view.size()) {
		logger::warn(
			"Skipped % out of % lidar frame messages.",
			lidar_frames_view.size() - num_lidar_frames,
			lidar_frames_view.size()
		);
	}

	return {};
}

} // namespace drm::lidar_parsers
