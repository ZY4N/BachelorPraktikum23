#include "helpers/transform_conversion.hpp"
#include "modules/frame_exporters/kitti.hpp"

#include "gtest/gtest.h"
#include <fstream>

TEST(frame_exporter, test_write_pose_to_removert_file_and_get_number_of_prev_frames) {
	const auto test_matrix = Eigen::Vector3d(1, 1, 1);
	const auto test_quaternoid = Eigen::Quaterniond(1, 1, 1, 1);
	auto test_transform = drm::types::transform_t();
	test_transform.translation = test_matrix;
	test_transform.rotation = test_quaternoid;
	const auto output_string = std::string("-3 0 4 1 4 -3 0 1 0 4 -3 1 ");
	auto error_code = drm::frame_exporters::kitti::write_pose("../../../test_resources", test_transform);
	ASSERT_EQ(error_code.value(), 0);
	std::ifstream input("../../../test_resources/pose.txt");
	std::string result;
	std::getline(input, result);
	ASSERT_EQ(output_string, result);
	std::filesystem::remove("../../../test_resources/pose.txt");
}

TEST(frame_exporter, test_write_points_to_removert_file) {
	const auto test_translation1 = drm::types::translation_t(1, 1, 1);
	const auto test_translation2 = drm::types::translation_t(2, 2, 2);
	const auto test_translation3 = drm::types::translation_t(3, 3, 3);
	std::vector<drm::types::translation_t> test_vektor{ test_translation1, test_translation2, test_translation3 };
	auto error_code = drm::frame_exporters::kitti::write_points("../../../test_resources", test_vektor, 3);
	ASSERT_EQ(error_code.value(), 0);
	std::error_code fs_error;
	ASSERT_EQ(true, std::filesystem::exists("../../../test_resources/000003.bin", fs_error));
	std::filesystem::remove("../../../test_resources/000003.bin");
}
