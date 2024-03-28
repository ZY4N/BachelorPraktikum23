#include "helpers/ros_time_conversion.hpp"

#include "gtest/gtest.h"

void test_conversions_at(std::uint32_t seconds, std::uint32_t nano_seconds) {
	namespace chr = std::chrono;
	using second_t = chr::duration<std::uint64_t>;
	using nano_second_t = chr::duration<std::uint64_t, std::nano>;

	const auto chr_seconds = second_t{ seconds };
	const auto chr_nano_seconds = nano_second_t{ nano_seconds };

	const auto correct_chr_ts = drm::types::timestamp_t{ chr_seconds + chr_nano_seconds };
	const auto correct_ros_ts = ros::Time{ seconds, nano_seconds };

	const auto result_chr_ts = drm::ros_time_to_timestamp_t(correct_ros_ts);
	const auto result_ros_ts = drm::timestamp_t_to_ros_time(correct_chr_ts);

	ASSERT_EQ(correct_chr_ts, result_chr_ts);
	ASSERT_EQ(correct_ros_ts, result_ros_ts);
}

TEST(ros_time_conversion, ros_max_time) {
	const auto max = ros::TIME_MAX;
	test_conversions_at(max.sec, max.nsec);
}

TEST(ros_time_conversion, ros_min_time) {
	const auto min = ros::TIME_MIN;
	test_conversions_at(min.sec, min.nsec);
}

TEST(ros_time_conversion, nano_seconds_less_than_seond) {
	const auto max = ros::TIME_MAX;
	test_conversions_at(1, max.nsec);
}

TEST(ros_time_conversion, test_all_nano_seconds) {
	// Why is testing taking so long?
	// The tests:
	const auto max = ros::TIME_MAX;
	for (std::uint32_t nsec{}; nsec != max.nsec; ++nsec) {
		test_conversions_at(42, nsec);
	}
}
