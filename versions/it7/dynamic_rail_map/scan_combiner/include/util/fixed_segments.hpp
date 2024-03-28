#pragma once

#include <cinttypes>
#include <cmath>
#include <limits>

/**
 * @class fixed_segment_iterator
 * @brief Iterator for traversing fixed-size segments within a range of integers.
 * @tparam Integer The integer type representing the segments.
 */
template<typename Integer>
class fixed_segment_iterator {
public:
	using value_type = std::pair<Integer, Integer>;
	using size_type = std::uint64_t;

	/**
	 * @brief Constructs a fixed_segment_iterator with the specified parameters.
	 *
	 * @param min		   The minimum value of the integer range.
	 * @param max		   The maximum value of the integer range.
	 * @param segment_size  The size of each segment.
	 * @param segment_index The index of the segment to iterate over.
	 */
	inline fixed_segment_iterator(
		const Integer& min, const Integer& max, const Integer& segment_size, const size_type& segment_index
	);

public:
	inline static fixed_segment_iterator make_begin(
		const Integer& min, const Integer& max, const Integer& segment_size
	);

	inline static fixed_segment_iterator make_end(const Integer& min, const Integer& max, const Integer& segment_size);

	inline fixed_segment_iterator& operator++();
	[[nodiscard]] inline fixed_segment_iterator operator+(size_type offset) const;
	[[nodiscard]] inline value_type operator*() const;
	[[nodiscard]] inline value_type operator[](size_type offset) const;

	[[nodiscard]] inline bool operator==(const fixed_segment_iterator&) const;
	[[nodiscard]] inline bool operator!=(const fixed_segment_iterator&) const;

private:
	const value_type m_full_segment;
	const Integer m_segment_size;
	size_type m_segment_index;
};

/**
 * @class fixed_segments
 * @brief Container representing fixed-size segments within a range of integers.
 * @tparam Integer The integer type representing the segments.
 */
template<typename Integer>
class fixed_segments {
public:
	using iterator = fixed_segment_iterator<Integer>;
	using value_type = typename iterator::value_type;
	using size_type = typename iterator::size_type;

	/**
	 * @brief Constructs a fixed_segments container with the specified parameters.
	 *
	 * @param min		   The minimum value of the integer range.
	 * @param max		   The maximum value of the integer range.
	 * @param segment_size  The size of each segment.
	 */
	inline fixed_segments(const Integer& min, const Integer& max, const Integer& segment_size);

	[[nodiscard]] inline const iterator& begin() const;
	[[nodiscard]] inline const iterator& end() const;

	[[nodiscard]] inline value_type operator[](size_type index) const;

private:
	fixed_segment_iterator<Integer> m_begin, m_end;
};

template<class Integer>
fixed_segments<Integer>::fixed_segments(const Integer& min, const Integer& max, const Integer& segment_size) :
	m_begin{ fixed_segment_iterator<Integer>::make_begin(min, max, segment_size) },
	m_end{ fixed_segment_iterator<Integer>::make_end(min, max, segment_size) } {
}

template<class Integer>
const typename fixed_segments<Integer>::iterator& fixed_segments<Integer>::begin() const {
	return m_begin;
}

template<class Integer>
const typename fixed_segments<Integer>::iterator& fixed_segments<Integer>::end() const {
	return m_end;
}

template<class Integer>
typename fixed_segments<Integer>::value_type fixed_segments<Integer>::operator[](const size_type index) const {
	return m_begin[index];
}

template<class Integer>
fixed_segment_iterator<Integer>::fixed_segment_iterator(
	const Integer& min, const Integer& max, const Integer& segment_size, const size_type& segment_index
) :
	m_full_segment{ min, max }, m_segment_size{ segment_size }, m_segment_index{ segment_index } {
}

template<class Integer>
fixed_segment_iterator<Integer> fixed_segment_iterator<Integer>::make_begin(
	const Integer& min, const Integer& max, const Integer& segment_size
) {
	return { min, max, segment_size, 0 };
}

template<class Integer>
fixed_segment_iterator<Integer> fixed_segment_iterator<Integer>::make_end(
	const Integer& min, const Integer& max, const Integer& segment_size
) {
	const auto num_segments = (max - min + segment_size - Integer{ 1 }) / segment_size;
	return { min, max, segment_size, num_segments };
}

template<class Integer>
typename fixed_segment_iterator<Integer>::value_type fixed_segment_iterator<Integer>::operator*() const {

	const auto relative_begin = m_segment_size * m_segment_index;

	// Mutable for rvo
	auto segment_begin = m_full_segment.first + relative_begin;
	auto segment_end = std::min(segment_begin + m_segment_size, m_full_segment.second);

	return { segment_begin, segment_end };
}

template<class Integer>
fixed_segment_iterator<Integer>& fixed_segment_iterator<Integer>::operator++() {
	++m_segment_index;
	return *this;
}

template<class Integer>
fixed_segment_iterator<Integer> fixed_segment_iterator<Integer>::operator+(const size_type offset) const {
	auto copy = *this;
	copy.m_segment_index += offset;
	return copy;
}

template<class Integer>
typename fixed_segment_iterator<Integer>::value_type fixed_segment_iterator<Integer>::operator[](const size_type offset
) const {
	return *(*this + offset);
}

template<class Integer>
bool fixed_segment_iterator<Integer>::operator==(const fixed_segment_iterator& other) const {
	return this->m_segment_index == other.m_segment_index and this->m_full_segment == other.m_full_segment and
		this->m_segment_size == other.m_segment_size;
}

template<class Integer>
bool fixed_segment_iterator<Integer>::operator!=(const fixed_segment_iterator& other) const {
	return not(*this == other);
}
