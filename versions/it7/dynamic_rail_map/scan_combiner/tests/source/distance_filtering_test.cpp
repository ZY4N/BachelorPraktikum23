#include "components/distance_filtering.hpp"

#include "gtest/gtest.h"

namespace {

// Test create_simple_filter
TEST(DistanceFilteringTest, CreateSimpleFilter) {
	const double max_distance = 5.0;
	const auto filter = drm::distance_filtering::create_simple_filter(max_distance);

	// Within the maximum distance
	ASSERT_TRUE(filter({ 4.0, 0.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, 3.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, 0.0, 2.0 }));
	ASSERT_TRUE(filter({ 3.0, 4.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, 0.0, 5.0 }));

	// Outside the maximum distance
	ASSERT_FALSE(filter({ 6.0, 0.0, 0.0 }));
	ASSERT_FALSE(filter({ 0.0, 0.0, 6.0 }));
}

// Test create_peripheral_filter
TEST(DistanceFilteringTest, CreatePeripheralFilter) {
	const double max_radial_distance = 5.0;
	const double max_peripheral_distance = 3.0;
	const auto filter = drm::distance_filtering::create_peripheral_filter(max_radial_distance, max_peripheral_distance);

	ASSERT_TRUE(filter({ 0.0, 0.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, 0.0, 3.0 }));
	ASSERT_FALSE(filter({ 0.0, 0.0, 4.0 }));

	ASSERT_TRUE(filter({ 3.0, 0.0, 0.0 }));
	ASSERT_TRUE(filter({ -3.0, 0.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, 3.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, -3.0, 0.0 }));
	ASSERT_TRUE(filter({ 0.0, 0.0, 3.0 }));
	ASSERT_TRUE(filter({ 0.0, 0.0, -3.0 }));

	ASSERT_FALSE(filter({ 3.5, 0.0, 0.0 }));
	ASSERT_FALSE(filter({ 0.0, 0.0, -3.5 }));
	ASSERT_FALSE(filter({ 3.5, 0, 3.5 }));
}

} // namespace
