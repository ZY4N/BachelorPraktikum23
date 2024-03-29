#include "helpers/transform_conversion.hpp"

#include "gtest/gtest.h"

namespace {

// Test translation_from with matrix
TEST(TransformConversionTest, TranslationFromMatrix) {
	const drm::types::matrix_t matrix = drm::types::matrix_t::Identity();
	const drm::types::translation_t expected_translation = { 0.0, 0.0, 0.0 };
	const auto result_translation = drm::translation_from(matrix);

	ASSERT_TRUE(expected_translation.isApprox(result_translation));
}

// Test translation_from with transform
TEST(TransformConversionTest, TranslationFromTransform) {
	const drm::types::transform_t transform = { { 1.0, 2.0, 3.0 }, { 0.0, 0.0, 0.0, 1.0 } };
	const drm::types::translation_t expected_translation = { 1.0, 2.0, 3.0 };
	const auto result_translation = drm::translation_from(transform);

	ASSERT_TRUE(expected_translation.isApprox(result_translation));
}

// Test rotation_from with matrix
TEST(TransformConversionTest, RotationFromMatrix) {
	const drm::types::matrix_t matrix = drm::types::matrix_t::Identity();
	const drm::types::rotation_t expected_rotation = { 1.0, 0.0, 0.0, 0.0 };
	const auto result_rotation = drm::rotation_from(matrix);

	ASSERT_TRUE(expected_rotation.isApprox(result_rotation));
}

// Test rotation_from with transform
TEST(TransformConversionTest, RotationFromTransform) {
	const drm::types::transform_t transform = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } };
	const drm::types::rotation_t expected_rotation = { 0.0, 0.0, 0.0, 1.0 };
	const auto result_rotation = drm::rotation_from(transform);

	ASSERT_TRUE(expected_rotation.isApprox(result_rotation));
}

// Test matrix_from with individual components
TEST(TransformConversionTest, MatrixFromIndividualComponents) {
	const double translation_x = 1.0;
	const double translation_y = 2.0;
	const double translation_z = 3.0;
	const double rotation_w = 1.0;
	const double rotation_x = 0.0;
	const double rotation_y = 0.0;
	const double rotation_z = 0.0;

	const drm::types::matrix_t expected_matrix = Eigen::Translation3d(1.0, 2.0, 3.0) *
		Eigen::Quaterniond(1.0, 0.0, 0.0, 0.0);
	const auto result_matrix = drm::matrix_from(
		translation_x,
		translation_y,
		translation_z,
		rotation_w,
		rotation_x,
		rotation_y,
		rotation_z
	);

	ASSERT_TRUE(expected_matrix.isApprox(result_matrix));
}

// Test matrix_from with vector and quaternion
TEST(TransformConversionTest, MatrixFromVectorQuaternion) {
	const drm::types::translation_t translation = { 1.0, 2.0, 3.0 };
	const drm::types::rotation_t rotation = { 1.0, 0.0, 0.0, 0.0 };

	const drm::types::matrix_t expected_matrix = Eigen::Translation3d(1.0, 2.0, 3.0) *
		Eigen::Quaterniond(1.0, 0.0, 0.0, 0.0);
	const auto result_matrix = drm::matrix_from(translation, rotation);

	ASSERT_TRUE(expected_matrix.isApprox(result_matrix));
}

// Test matrix_from with transform
TEST(TransformConversionTest, MatrixFromTransform) {
	const drm::types::transform_t transform = { { 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0, 0.0 } };
	const drm::types::matrix_t expected_matrix = Eigen::Translation3d(1.0, 2.0, 3.0) *
		Eigen::Quaterniond(1.0, 0.0, 0.0, 0.0);
	const auto result_matrix = drm::matrix_from(transform);

	ASSERT_TRUE(expected_matrix.isApprox(result_matrix));
}

// Test transform_from with individual components
TEST(transform_conversion, transform_from_individual_components) {
	const double translation_x = 1.0;
	const double translation_y = 2.0;
	const double translation_z = 3.0;
	const double rotation_w = 1.0;
	const double rotation_x = 0.0;
	const double rotation_y = 0.0;
	const double rotation_z = 0.0;

	const drm::types::transform_t expected_transform = { { 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0, 0.0 } };
	const drm::types::transform_t result_transform = drm::transform_from(
		translation_x,
		translation_y,
		translation_z,
		rotation_w,
		rotation_x,
		rotation_y,
		rotation_z
	);

	const auto translation_equal = expected_transform.translation.isApprox(
		result_transform.translation,
		1e-6
	); // Adjust the epsilon value as needed
	const auto rotation_equal = expected_transform.rotation.isApprox(
		result_transform.rotation,
		1e-6
	); // Adjust the epsilon value as needed

	ASSERT_TRUE(translation_equal && rotation_equal);
}

// Test transform_from with matrix
TEST(transform_conversion, transform_from_matrix) {
	const drm::types::matrix_t matrix = Eigen::Translation3d(1.0, 2.0, 3.0) * Eigen::Quaterniond(1.0, 0.0, 0.0, 0.0);
	const drm::types::transform_t expected_transform = { { 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0, 0.0 } };
	const drm::types::transform_t result_transform = drm::transform_from(matrix);

	const auto translation_equal = expected_transform.translation.isApprox(
		result_transform.translation,
		1e-6
	); // Adjust the epsilon value as needed
	const auto rotation_equal = expected_transform.rotation.isApprox(
		result_transform.rotation,
		1e-6
	); // Adjust the epsilon value as needed

	ASSERT_TRUE(translation_equal && rotation_equal);
}

// Test transform_from with vector and quaternion
TEST(transform_conversion, transform_from_vector_quaternion) {
	const drm::types::matrix_t matrix = Eigen::Translation3d(1.0, 2.0, 3.0) * Eigen::Quaterniond(1.0, 0.0, 0.0, 0.0);
	const drm::types::transform_t expected_transform = { { 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0, 0.0 } };
	const drm::types::transform_t result_transform = drm::transform_from(matrix);

	const auto translation_equal = expected_transform.translation.isApprox(
		result_transform.translation,
		1e-6
	); // Adjust the epsilon value as needed
	const auto rotation_equal = expected_transform.rotation.isApprox(
		result_transform.rotation,
		1e-6
	); // Adjust the epsilon value as needed

	ASSERT_TRUE(translation_equal && rotation_equal);
}

// Test extractEulerAngleXYZ
TEST(TransformConversionTest, ExtractEulerAngleXYZ) {
	const drm::types::matrix_t matrix = drm::types::matrix_t::Identity();
	double t1, t2, t3;

	// Expected angle
	const double expected_t1 = 0.0;
	const double expected_t2 = 0.0;
	const double expected_t3 = 0.0;

	drm::extractEulerAngleXYZ(matrix, t1, t2, t3);

	// Tolerance
	const double tolerance = 1e-6;

	ASSERT_NEAR(expected_t1, t1, tolerance);
	ASSERT_NEAR(expected_t2, t2, tolerance);
	ASSERT_NEAR(expected_t3, t3, tolerance);
}

} // namespace
