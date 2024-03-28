#pragma once

#include <tuple>

/**
 * @brief Invokes a function with the element at specified index in given tuple.
 *
 * @tparam F     The type of the function to apply.
 * @tparam Tuple The type of the tuple.
 * @param f      The function to apply to the element at the specified index.
 * @param t      The tuple whose element will be used as an argument for the function.
 * @param index  The index of the element in the tuple to apply the function to.
 *
 * @return true if the function was applied to the element at the specified index, false otherwise.
 */
template<class F, class Tuple>
inline constexpr bool apply_at_index(F&& f, Tuple&& t, const std::size_t index) {
	return std::apply(
		[&](const auto&... elements) {
			if (index >= sizeof...(elements)) {
				return false; // Index out of bounds
			}
			auto curr_index = std::size_t{};
			return ((curr_index++ == index ? (f(elements), true) : false) or ...);
		},
		std::forward<Tuple>(t)
	);
}
