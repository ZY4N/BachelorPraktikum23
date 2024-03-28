#pragma once

#include "types.hpp"


namespace drm {

inline types::translation_t translation_from(
	const types::matrix_t& matrix
) {
	return matrix.matrix().block<3, 1>(0, 3);
}

inline types::translation_t translation_from(
	const types::transform_t& transform
) {
	return transform.translation;
}


inline types::rotation_t rotation_from(
	const types::matrix_t& matrix
) {
	return types::rotation_t{ matrix.matrix().block<3, 3>(0, 0) };
}

inline types::rotation_t rotation_from(
	const types::transform_t& transform
) {
	return transform.rotation;
}

inline types::matrix_t matrix_from(
	const double& translation_x,
	const double& translation_y,
	const double& translation_z,
	const double& rotation_w,
	const double& rotation_x,
	const double& rotation_y,
	const double& rotation_z
) {
	return {
		Eigen::Translation3d(translation_x, translation_y, translation_z) *
			Eigen::Quaterniond(rotation_w, rotation_x, rotation_y, rotation_z)
	};
}

template<typename Vector, typename Quaternion>
inline types::matrix_t matrix_from(
	const Vector& translation,
	const Quaternion& rotation
) {
	if constexpr (
		std::is_same_v<std::remove_cv_t<std::remove_reference_t<Vector>>, types::translation_t> and
			std::is_same_v<std::remove_cv_t<std::remove_reference_t<Quaternion>>, types::rotation_t>
		) {
		return {
			reinterpret_cast<const Eigen::Translation3d&>(translation) * rotation
		};
	} else {
		return {
			Eigen::Translation3d(translation.x, translation.y, translation.z) *
				Eigen::Quaterniond(rotation.w, rotation.x, rotation.y, rotation.z)
		};
	}
}

inline types::matrix_t matrix_from(
	const types::transform_t& transform
) {
	return {
		reinterpret_cast<const Eigen::Translation3d&>(transform.translation) * transform.rotation
	};
}

inline types::transform_t transform_from(
	const double& translation_x,
	const double& translation_y,
	const double& translation_z,
	const double& rotation_w,
	const double& rotation_x,
	const double& rotation_y,
	const double& rotation_z
) {
	return {
		{ translation_x, translation_y, translation_z },
		{ rotation_w, rotation_x, rotation_y, rotation_z }
	};
}

inline types::transform_t transform_from(
	const types::matrix_t& matrix
) {
	return {
		translation_from(matrix),
		rotation_from(matrix)
	};
}

template<typename Vector, typename Quaternion>
inline types::transform_t transform_from(
	const Vector& translation,
	const Quaternion& rotation
) {
	if constexpr (
		std::is_same_v<std::remove_cv_t<std::remove_reference_t<Vector>>, types::translation_t> and
			std::is_same_v<std::remove_cv_t<std::remove_reference_t<Quaternion>>, types::rotation_t>
		) {
		return { translation, rotation };
	} else {
		return {
			{ translation.x, translation.y, translation.z },
			{ rotation.w, rotation.x, rotation.y, rotation.z }
		};
	}
}

} // namespace drm