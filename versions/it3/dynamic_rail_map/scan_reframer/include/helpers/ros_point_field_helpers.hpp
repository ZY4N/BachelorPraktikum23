#pragma once
#include "span.hpp"

#include <sensor_msgs/PointField.h>

namespace drm {

/**
 * @brief Create a @c PointField with specified parameters.
 *
 * @param name      The name of the field.
 * @param offset    The byte offset of the field within the data structure.
 * @param datatype  The data type of the field. Should be one of the constants defined in @c PointField (e.g., INT8,
 *                  UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64).
 * @param count     The number of elements in the field.
 *
 * @return          An instance of sensor_msgs::PointField initialized with the provided parameters.
 */
[[nodiscard]] inline sensor_msgs::PointField make_point_field(
	std::string_view name, std::uint32_t offset, std::uint8_t datatype, std::uint32_t count
) noexcept;

/**
 * @brief Check if the given @c PointFields contains required @c PointFields and calculate the size.
 *
 * This function checks if the given set of @c PointFields contains the required set of @c PointFields.
 * Additionally, it calculates the size of the resulting data structure based on the offset and size
 * of the fields in the given set.
 *
 * @param required  A span representing the required set of @c PointField.
 * @param given     A span representing the given set of @c PointField to be checked.
 *
 * @return          A pair where the first element is a boolean indicating whether all required fields
 *                  are satisfied, and the second element is the calculated size of the resulting data structure.
 */
[[nodiscard]] inline std::pair<bool, std::size_t> check_fields(
	tcb::span<const sensor_msgs::PointField> required, tcb::span<const sensor_msgs::PointField> given
) noexcept;

/**
 * @brief Get the size (in bytes) of a @c PointField data type.
 *
 * @note            The function asserts if an unsupported data type is provided, indicating a programming error.
 *
 * @param datatype  The data type of the @c PointField whose size needs to be determined.
 *
 * @return          The size (in bytes) of the @c PointField based on its data type.
 */
[[nodiscard]] inline std::size_t size_of_point_field(std::uint8_t datatype) noexcept;

/**
 * @brief Read a value of type @c T from a byte sequence at the specified offset.
 *
 * This template function reads a value of type @c T from a byte sequence represented by the given span
 * starting at the specified offset. It performs a byte-wise copy of the data, ensuring proper alignment
 * and avoiding undefined behavior.
 *
 * @note              The function asserts that the specified offset, along with the size of type @c T, does
 *                    not exceed the size of the byte sequence.
 *
 * @tparam T          The type of the value to be read.
 * @param bytes       A span representing the byte sequence from which to read the value.
 * @param offset      The byte offset within the byte sequence from where to start reading.
 *
 * @return            The value of type @c T read from the byte sequence at the specified offset.
 */
template<typename SrcType, typename DstType>
[[nodiscard]] inline DstType read_point_field(tcb::span<const std::uint8_t> bytes, std::uint32_t offset) noexcept;

} // namespace drm

#define INCLUDE_POINT_FIELD_HELPERS_IMPLEMENTATION
#include "helpers/ros_point_field_helpers.ipp"
#undef INCLUDE_POINT_FIELD_HELPERS_IMPLEMENTATION
