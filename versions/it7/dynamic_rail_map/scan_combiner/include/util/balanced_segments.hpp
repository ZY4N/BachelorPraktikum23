#pragma once

#include <cinttypes>
#include <cmath>
#include <limits>

/**
 * @class balanced_segment_iterator
 * @brief Iterator for traversing balanced segments within a range of integers.
 * @tparam Integer The integer type representing the segments.
 */
template<typename Integer>
class balanced_segment_iterator {
public:
	using value_type = std::pair<Integer, Integer>;
	using size_type = std::uint64_t;

public:
	[[nodiscard]] inline static balanced_segment_iterator make_begin(
		const Integer& begin, const Integer& end, const size_type& num_segments
	);

	[[nodiscard]] inline static balanced_segment_iterator make_end(
		const Integer& begin, const Integer& end, const size_type& num_segments
	);

	inline balanced_segment_iterator& operator++();
	[[nodiscard]] inline balanced_segment_iterator operator+(size_type offset) const;
	[[nodiscard]] inline value_type operator*() const;
	[[nodiscard]] inline value_type operator[](size_type offset) const;

	[[nodiscard]] inline bool operator==(const balanced_segment_iterator&) const;
	[[nodiscard]] inline bool operator!=(const balanced_segment_iterator&) const;

private:
	inline balanced_segment_iterator(
		const Integer& begin, const Integer& end, const size_type& num_segments, const size_type& segment_index
	);

private:
	const Integer m_begin, m_min_segment_size, m_remaining_values;
	size_type m_segment_index;
};

/**
 * @class balanced_segments
 * @brief Container representing balanced segments within a range of integers.
 * @tparam Integer The integer type representing the segments.
 */
template<typename Integer>
class balanced_segments {
public:
	using iterator = balanced_segment_iterator<Integer>;
	using value_type = typename iterator::value_type;
	using size_type = typename iterator::size_type;

public:
	/**
	 * @brief Constructs a balanced_segments container with the specified parameters.
	 *
	 * @param begin		    The beginning of the integer range.
	 * @param end		    The end of the integer range.
	 * @param num_segments  The number of segments to divide the range into.
	 */
	inline balanced_segments(const Integer& begin, const Integer& end, const size_type& num_segments);

	[[nodiscard]] inline const iterator& begin() const;
	[[nodiscard]] inline const iterator& end() const;

	value_type operator[](std::size_t index) const;

private:
	iterator m_begin, m_end;
};

template<class Integer>
balanced_segments<Integer>::balanced_segments(const Integer& begin, const Integer& end, const size_type& num_segments) :
	m_begin{ balanced_segment_iterator<Integer>::make_begin(begin, end, num_segments) },
	m_end{ balanced_segment_iterator<Integer>::make_end(begin, end, num_segments) } {
}

template<class Integer>
const typename balanced_segments<Integer>::iterator& balanced_segments<Integer>::begin() const {
	return m_begin;
}

template<class Integer>
const typename balanced_segments<Integer>::iterator& balanced_segments<Integer>::end() const {
	return m_end;
}

template<class Integer>
typename balanced_segments<Integer>::value_type balanced_segments<Integer>::operator[](std::size_t index) const {
	return m_begin[index];
}

template<class Integer>
balanced_segment_iterator<Integer>::balanced_segment_iterator(
	const Integer& begin, const Integer& end, const size_type& num_segments, const size_type& segment_index
) :
	m_begin{ begin },
	m_min_segment_size{ (end - begin) / Integer{ num_segments } },
	m_remaining_values{ (end - begin) % Integer{ num_segments } },
	m_segment_index{ segment_index } {
}

template<class Integer>
balanced_segment_iterator<Integer> balanced_segment_iterator<Integer>::make_begin(
	const Integer& begin, const Integer& end, const size_type& num_segments
) {
	return { begin, end, num_segments, 0 };
}

template<class Integer>
balanced_segment_iterator<Integer> balanced_segment_iterator<Integer>::make_end(
	const Integer& begin, const Integer& end, const size_type& num_segments
) {
	return { begin, end, num_segments, num_segments };
}

template<class Integer>
typename balanced_segment_iterator<Integer>::value_type balanced_segment_iterator<Integer>::operator*() const {

	const auto index_integer = Integer{ m_segment_index };

	// Mutable for rvo
	auto segment_begin = m_begin + m_segment_index * m_min_segment_size +
		std::min(Integer{ m_segment_index }, m_remaining_values);
	auto segment_end = segment_begin + m_min_segment_size + Integer{ size_type{ index_integer < m_remaining_values } };

	return { segment_begin, segment_end };
}

template<class Integer>
balanced_segment_iterator<Integer>& balanced_segment_iterator<Integer>::operator++() {
	++m_segment_index;
	return *this;
}

template<class Integer>
balanced_segment_iterator<Integer> balanced_segment_iterator<Integer>::operator+(const size_type offset) const {
	auto copy = *this;
	copy.m_segment_index += offset;
	return copy;
}

template<class Integer>
typename balanced_segment_iterator<Integer>::value_type balanced_segment_iterator<Integer>::operator[](
	const size_type offset
) const {
	return *(*this + offset);
}

template<class Integer>
bool balanced_segment_iterator<Integer>::operator==(const balanced_segment_iterator& other) const {
	return this->m_segment_index == other.m_segment_index and this->m_begin == other.m_begin and
		this->m_min_segment_size == other.m_min_segment_size and this->m_remaining_values == other.m_remaining_values;
}

template<class Integer>
bool balanced_segment_iterator<Integer>::operator!=(const balanced_segment_iterator& other) const {
	return not(*this == other);
}
