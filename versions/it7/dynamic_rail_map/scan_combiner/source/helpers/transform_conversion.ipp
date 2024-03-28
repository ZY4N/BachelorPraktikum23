#ifndef INCLUDE_TRANSFORM_CONVERSION_IMPLEMENTATION
#	error Never include this file directly include 'transform_conversion.hpp'
#endif

namespace drm {

types::translation_t translation_from(const types::matrix_t& matrix) noexcept {
	return matrix.matrix().block<3, 1>(0, 3);
}

types::translation_t translation_from(const types::transform_t& transform) noexcept {
	return transform.translation;
}

types::rotation_t rotation_from(const types::matrix_t& matrix) noexcept {
	return types::rotation_t{ matrix.matrix().block<3, 3>(0, 0) };
}

types::rotation_t rotation_from(const types::transform_t& transform) noexcept {
	return transform.rotation;
}

types::matrix_t matrix_from(
	const double& translation_x,
	const double& translation_y,
	const double& translation_z,
	const double& rotation_w,
	const double& rotation_x,
	const double& rotation_y,
	const double& rotation_z
) noexcept {
	return { Eigen::Translation3d(translation_x, translation_y, translation_z) *
		     Eigen::Quaterniond(rotation_w, rotation_x, rotation_y, rotation_z) };
}

template<typename Vector, typename Quaternion>
types::matrix_t matrix_from(const Vector& translation, const Quaternion& rotation) noexcept {
	if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<Vector>>, types::translation_t> and std::is_same_v<std::remove_cv_t<std::remove_reference_t<Quaternion>>, types::rotation_t>) {
		return { reinterpret_cast<const Eigen::Translation3d&>(translation) * rotation };
	} else {
		return { Eigen::Translation3d(translation.x, translation.y, translation.z) *
			     Eigen::Quaterniond(rotation.w, rotation.x, rotation.y, rotation.z) };
	}
}

types::matrix_t matrix_from(const types::transform_t& transform) noexcept {
	return { reinterpret_cast<const Eigen::Translation3d&>(transform.translation) * transform.rotation };
}

types::transform_t transform_from(
	const double& translation_x,
	const double& translation_y,
	const double& translation_z,
	const double& rotation_w,
	const double& rotation_x,
	const double& rotation_y,
	const double& rotation_z
) noexcept {
	return { { translation_x, translation_y, translation_z }, { rotation_w, rotation_x, rotation_y, rotation_z } };
}

types::transform_t transform_from(const types::matrix_t& matrix) noexcept {
	return { translation_from(matrix), rotation_from(matrix) };
}

template<typename Vector, typename Quaternion>
types::transform_t transform_from(const Vector& translation, const Quaternion& rotation) noexcept {
	if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<Vector>>, types::translation_t> and std::is_same_v<std::remove_cv_t<std::remove_reference_t<Quaternion>>, types::rotation_t>) {
		return { translation, rotation };
	} else {
		return { { translation.x, translation.y, translation.z }, { rotation.w, rotation.x, rotation.y, rotation.z } };
	}
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

} // namespace drm
