#ifndef INCLUDE_ROS_TIME_CONVERSION_IMPLEMENTATION
#	error Never include this file directly include 'ros_time_conversion.hpp'
#endif

namespace drm {

ros::Time timestamp_t_to_ros_time(const types::timestamp_t& timestamp) noexcept {
	using timestamp_seconds_t = std::chrono::duration<std::uint32_t>;
	using timestamp_nano_seconds_t = std::chrono::duration<std::uint32_t, std::nano>;
	using std::chrono::duration_cast;

	// duration_cast truncates integer and therefore rounds down to next second.
	const auto secs = duration_cast<timestamp_seconds_t>(timestamp);
	const auto nsecs = duration_cast<timestamp_nano_seconds_t>(timestamp - secs);

	return { secs.count(), nsecs.count() };
}

types::timestamp_t ros_time_to_timestamp_t(const ros::Time& timestamp) noexcept {
	using timestamp_seconds_t = std::chrono::duration<std::uint32_t>;
	using std::chrono::duration_cast;

	const auto secs = timestamp_seconds_t{ timestamp.sec };
	const auto nsecs = types::timestamp_t{ timestamp.nsec };

	return { duration_cast<types::timestamp_t>(secs) + nsecs };
}

} // namespace drm
