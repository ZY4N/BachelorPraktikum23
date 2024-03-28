#pragma once

#include <cinttypes>

/**
 * @class unique_enum_type
 * @brief A type-safe wrapper for unique identifiers used as enum values.
 *
 * This template struct provides a type-safe wrapper for unique identifiers used as enum values.
 * Each instance of unique_enum_type is associated with a unique index value, ensuring type safety
 * when comparing or using enum-like values.
 *
 * @tparam UniqueIdentifier An identifier for distinguishing different instances of unique_enum_type.
 */
template<std::size_t UniqueIdentifier>
struct unique_enum_type {

	using index_type = std::size_t;

	/**
	 * @brief Constructs a unique_enum_type with the specified index.
	 *
	 * @param idx The index value associated with the unique_enum_type instance.
	 */
	inline constexpr unique_enum_type(const index_type idx) : index{ idx } {
	}

	[[nodiscard]] inline constexpr bool operator==(const unique_enum_type& other) const {
		return index == other.index;
	}

	[[nodiscard]] inline constexpr bool operator!=(const unique_enum_type& other) const {
		return not(*this == other);
	}

	[[nodiscard]] inline constexpr bool operator<(const unique_enum_type& other) const {
		return index < other.index;
	}

	[[nodiscard]] inline constexpr bool operator>(const unique_enum_type& other) const {
		return other < *this;
	}

	[[nodiscard]] inline constexpr bool operator<=(const unique_enum_type& other) const {
		return !(other < *this);
	}

	[[nodiscard]] inline constexpr bool operator>=(const unique_enum_type& other) const {
		return !(*this < other);
	}

	index_type index;
};
