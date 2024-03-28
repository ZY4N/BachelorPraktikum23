#pragma once

#include "types.hpp"

namespace drm {

/**
 * @brief Extract translation information from a 4x4 transformation matrix.
 *
 * This function takes a 4x4 transformation matrix and extracts the translation vector
 * represented by the first three elements of the last column in the matrix.
 *
 * @param matrix      The 4x4 transformation matrix.
 *
 * @return            A @c types::translation_t representing the extracted translation.
 */
[[nodiscard]] inline types::translation_t translation_from(const types::matrix_t& matrix) noexcept;

/**
 * @brief Extract translation information from a @c types::transform_t.
 *
 * This function takes a transformation represented by a translation and rotation and extracts the
 * translation vector.
 *
 * @param transform   The @c types::transform_t representing translation and rotation.
 *
 * @return            A @c types::translation_t representing the extracted translation.
 */
[[nodiscard]] inline types::translation_t translation_from(const types::transform_t& transform) noexcept;

/**
 * @brief Extract rotation information from a 4x4 transformation matrix.
 *
 * This function takes a 4x4 transformation matrix and extracts the rotation quaternion
 * representation from the upper-left 3x3 submatrix.
 *
 * @param matrix      The 4x4 transformation matrix.
 *
 * @return            A @c types::rotation_t representing the extracted rotation.
 */
[[nodiscard]] inline types::rotation_t rotation_from(const types::matrix_t& matrix) noexcept;

/**
 * @brief Extract rotation information from a @c types::transform_t.
 *
 * This function takes a transformation represented by a translation and rotation and extracts the
 * rotation quaternion.
 *
 * @param transform   The @c types::transform_t representing translation and rotation.
 *
 * @return            A @c types::rotation_t representing the extracted rotation.
 */
[[nodiscard]] inline types::rotation_t rotation_from(const types::transform_t& transform) noexcept;

/**
 * @brief Create a 4x4 transformation matrix from translation and rotation components.
 *
 * This function creates a 4x4 transformation matrix using the provided translation and rotation components.
 *
 * @param translation_x  The X component of the translation vector.
 * @param translation_y  The Y component of the translation vector.
 * @param translation_z  The Z component of the translation vector.
 * @param rotation_w     The scalar (W) component of the rotation quaternion.
 * @param rotation_x     The X component of the rotation quaternion.
 * @param rotation_y     The Y component of the rotation quaternion.
 * @param rotation_z     The Z component of the rotation quaternion.
 *
 * @return               A @c types::matrix_t representing the constructed transformation matrix.
 */
[[nodiscard]] inline types::matrix_t matrix_from(
	const double& translation_x,
	const double& translation_y,
	const double& translation_z,
	const double& rotation_w,
	const double& rotation_x,
	const double& rotation_y,
	const double& rotation_z
) noexcept;

/**
 * @brief Create a 4x4 transformation matrix from given translation and rotation.
 *
 * This function creates a 4x4 transformation matrix using the provided translation vector and rotation quaternion.
 *
 * @tparam Vector      The vector type representing translation.
 * @tparam Quaternion  The quaternion type representing rotation.
 *
 * @param translation  The translation vector.
 * @param rotation     The rotation quaternion.
 *
 * @return             A @c types::matrix_t representing the constructed transformation matrix.
 */
template<typename Vector, typename Quaternion>
[[nodiscard]] inline types::matrix_t matrix_from(const Vector& translation, const Quaternion& rotation) noexcept;

/**
 * @brief Create a 4x4 transformation matrix from a @c types::transform_t.
 *
 * This function creates a 4x4 transformation matrix using the translation and rotation components
 * from the provided @c types::transform_t.
 *
 * @param transform    The @c types::transform_t representing translation and rotation.
 *
 * @return             A @c types::matrix_t representing the constructed transformation matrix.
 */
[[nodiscard]] inline types::matrix_t matrix_from(const types::transform_t& transform) noexcept;

/**
 * @brief Create a @c types::transform_t from translation and rotation components.
 *
 * This function creates a @c types::transform_t using the provided translation and rotation components.
 *
 * @param translation_x  The X component of the translation vector.
 * @param translation_y  The Y component of the translation vector.
 * @param translation_z  The Z component of the translation vector.
 * @param rotation_w     The scalar (W) component of the rotation quaternion.
 * @param rotation_x     The X component of the rotation quaternion.
 * @param rotation_y     The Y component of the rotation quaternion.
 * @param rotation_z     The Z component of the rotation quaternion.
 *
 * @return               A @c types::transform_t representing the constructed transformation.
 */
[[nodiscard]] inline types::transform_t transform_from(
	const double& translation_x,
	const double& translation_y,
	const double& translation_z,
	const double& rotation_w,
	const double& rotation_x,
	const double& rotation_y,
	const double& rotation_z
) noexcept;

/**
 * @brief Create a @c types::transform_t from a 4x4 transformation matrix.
 *
 * This function creates a @c types::transform_t using the translation and rotation components
 * from the provided 4x4 transformation matrix.
 *
 * @param matrix       The @c types::matrix_t representing the transformation matrix.
 *
 * @return             A @c types::transform_t representing the constructed transformation.
 */
[[nodiscard]] inline types::transform_t transform_from(const types::matrix_t& matrix) noexcept;

/**
 * @brief Create a @c types::transform_t from given translation and rotation.
 *
 * This function creates a @c types::transform_t using the provided translation vector and rotation quaternion.
 *
 * @tparam Vector      The vector type representing translation.
 * @tparam Quaternion  The quaternion type representing rotation.
 *
 * @param translation  The translation vector.
 * @param rotation     The rotation quaternion.
 *
 * @return             A @c types::transform_t representing the constructed transformation.
 */
template<typename Vector, typename Quaternion>
[[nodiscard]] inline types::transform_t transform_from(const Vector& translation, const Quaternion& rotation) noexcept;

} // namespace drm

#define INCLUDE_TRANSFORM_CONVERSION_IMPLEMENTATION
#include "helpers/transform_conversion.ipp"
#undef INCLUDE_TRANSFORM_CONVERSION_IMPLEMENTATION
