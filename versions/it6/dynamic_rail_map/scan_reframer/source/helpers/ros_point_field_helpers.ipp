#ifndef INCLUDE_POINT_FIELD_HELPERS_IMPLEMENTATION
#	error Never include this file directly include 'ros_point_field_helpers.hpp'
#endif

#include "util/logger.hpp"

#include <algorithm>
#include <numeric>
#include <sensor_msgs/PointField.h>

namespace drm {

sensor_msgs::PointField make_point_field(
	const std::string_view name, const std::uint32_t offset, const std::uint8_t datatype, const std::uint32_t count
) noexcept {
	auto field = sensor_msgs::PointField{};
	field.name = name;
	field.offset = offset;
	field.datatype = datatype;
	field.count = count;
	return field;
}

[[nodiscard]] inline std::size_t size_of_point_field(const std::uint8_t datatype) noexcept {
	switch (datatype) {
	case sensor_msgs::PointField::INT8:
	case sensor_msgs::PointField::UINT8:
		return 1;
	case sensor_msgs::PointField::INT16:
	case sensor_msgs::PointField::UINT16:
		return 2;
	case sensor_msgs::PointField::INT32:
	case sensor_msgs::PointField::UINT32:
	case sensor_msgs::PointField::FLOAT32:
		return 4;
	case sensor_msgs::PointField::FLOAT64:
		return 8;
	default:
		assert(false);
	}
}

std::pair<bool, std::size_t> check_fields(
	tcb::span<const sensor_msgs::PointField> required, tcb::span<const sensor_msgs::PointField> given
) noexcept {

	std::vector<bool> is_satisfied(required.size(), false);

	auto size = std::size_t{};

	for (const auto& field : given) {

		logger::debug(
			"field name: '%' offset: % type: % count %",
			field.name,
			field.offset,
			static_cast<int>(field.datatype),
			field.count
		);

		const auto field_size = size_of_point_field(field.datatype);
		size = std::max(size, static_cast<std::size_t>(field.offset + field_size));

		for (std::size_t i{}; i != required.size(); ++i) {
			if (not is_satisfied[i]) {
				if (required[i] == field) {
					is_satisfied[i] = true;
					break;
				}
			}
		}
	}

	const auto all_satisfied = std::all_of(is_satisfied.begin(), is_satisfied.end(), [](const auto& b) { return b; });

	return { all_satisfied, size };
}

template<typename T>
T read_point_field(tcb::span<const std::uint8_t> bytes, const std::uint32_t offset) noexcept {
	assert(offset + sizeof(T) <= bytes.size());
	T value;
	// The use of std::memcpy is unavoidable in this case because
	// std::copy does not allow for different types and reinterpret_cast leads to UB.
	std::memcpy(&value, bytes.data() + offset, sizeof(value));
	return value;
}

} // namespace drm
