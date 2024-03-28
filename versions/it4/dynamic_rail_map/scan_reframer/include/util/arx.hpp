#pragma once

#include "span.hpp"

#include <algorithm>
#include <charconv>
#include <filesystem>
#include <functional>
#include <limits>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace arx_internal {

inline constexpr char no_short_flag = '\0';

using default_parser = std::nullptr_t;

template<auto ID, typename T, typename Parser>
struct flag {
	using type = T;
	static constexpr auto id{ ID };
	char short_name{ no_short_flag };
	std::string_view long_name;
	Parser parse{};
};

} // namespace arx_internal

/**
 * @brief function to create new flags that uses a default parser and only uses
 * a long name
 *
 * @tparam Enum      name of the flag that has to be defined in an enum
 * @tparam T         return type
 * @param long_name  String to use to call the flag
 * @return           a new flag
 */
template<auto Enum, typename T = bool>
[[nodiscard]] inline constexpr arx_internal::flag<Enum, T, arx_internal::default_parser> make_arx_flag(
	std::string_view long_name
);

/**
 * @brief function to create new flags that uses a default parser and has both,
 * a short and a long name
 *
 * @tparam Enum       name of the flag that has to be defined in an enum
 * @tparam T          T return type
 * @param short_name  Char to use to call the flag
 * @param long_name   String to use to call the flag
 * @return            a new flag
 */
template<auto Enum, typename T = bool>
[[nodiscard]] inline constexpr arx_internal::flag<Enum, T, arx_internal::default_parser> make_arx_flag(
	char short_name, std::string_view long_name
);

/**
 * @brief function to create new flags that uses a custom parser and only uses a
 * long name
 *
 * @tparam Enum      name of the flag that has to be defined in an enum
 * @tparam T         T return type
 * @tparam Parser    custom parser to parse the flag
 * @param long_name  String to use to call the flag
 * @param parser     custom parser
 * @return           a new flag
 */
template<auto Enum, typename T, typename Parser>
[[nodiscard]] inline constexpr arx_internal::flag<Enum, T, Parser> make_arx_flag(
	std::string_view long_name, Parser&& parser
);

/**
 * @brief function to create new flags that uses a custom parser and has both, a
 * short and a long name
 *
 * @tparam Enum       name of the flag that has to be defined in an enum
 * @tparam T          T return type
 * @tparam Parser     custom parser to parse the flag
 * @param short_name  Char to use to call the flag
 * @param long_name   String to use to call the flag
 * @param parser      custom parser
 * @return            a new flag
 */
template<auto Enum, typename T, typename Parser>
[[nodiscard]] inline constexpr arx_internal::flag<Enum, T, Parser> make_arx_flag(
	char short_name, std::string_view long_name, Parser&& parser
);

using arx_ssize_t = std::make_signed_t<std::size_t>;

/**
 * @brief tamplate for a custom number of flags to use for parsing;
 *
 * @note if something has been stated multiple times, the last entry counts
 *
 * @tparam Flags  an indefinite number of flags
 */
template<typename... Flags>
class arx {
private:
	static constexpr auto short_flag_prefix = std::string_view{ "-" };
	static constexpr auto long_flag_prefix = std::string_view{ "--" };
	using flag_tuple_t = std::tuple<Flags...>;

public:
	/**
	 * @brief constructor to initialize the flags
	 *
	 * @param num_args  number of arguments
	 * @param args      arguments
	 * @param flags     flags to use for parsing
	 */
	inline arx(int num_args, const char* const * args, Flags&&... flags);

	/**
	 *@brief function to retrieve content of flags
	 *
	 * @tparam FlagID name of the flag whose content is to be retrieved
	 * @return content of the flag
	 */
	template<auto FlagID>
	[[nodiscard]] inline auto get() const;

	/**
	 * @brief fuction to retrieve positionals (content in arguments that is not
	 * part of the flags)
	 *
	 * @return content of positionals
	 */
	[[nodiscard]] inline const std::vector<std::string_view>& get_positionals() const;

protected:
	[[nodiscard]] inline std::optional<std::string_view> find_flag_value(arx_ssize_t flag_index) const;

	template<class Flag>
	[[nodiscard]] inline std::optional<typename Flag::type> parse_value(Flag& flag, const std::string_view& value_str)
		const;

private:
	template<typename Flag>
	[[nodiscard]] inline bool matches_flag(char short_name, std::string_view long_name, std::string_view argument);

	struct bound_argument {
		inline bound_argument(const arx_ssize_t& new_flag_index, const std::string_view& new_value) :
			flag_index{ new_flag_index }, value{ new_value } {
		}

		arx_ssize_t flag_index;
		std::string_view value;
	};

private:
	flag_tuple_t m_flags;
	std::vector<bound_argument> m_bound_arguments{};
	std::vector<std::string_view> m_unbound_arguments{};
};

/**
 * @brief custom parsers
 */
namespace arx_parsers {

/**
 * @brief custom parser for chrono literals
 *
 * @tparam Type  type of the object to be parsed
 * @param str    object to be parsed
 * @return       chrono literal value of str
 */
template<class Duration = std::chrono::duration<double, std::ratio<1>>>
[[nodiscard]] inline std::optional<Duration> time(const std::string_view& str);

/**
 * @brief custom parser for integer values
 *
 * @tparam Type  type of the object to be parsed; per default int
 * @tparam Base  base of the object to be parsed; per default 10
 * @param str    object to be parsed
 * @return       int value of str
 */
template<typename Type = int, int Base = 10, typename = std::enable_if_t<std::is_integral_v<Type> and (Base > 0)>>
[[nodiscard]] inline std::optional<Type> integer(const std::string_view& str);

/**
 * @brief custom parser for float values
 *
 * @tparam Type    type of the object to be parsed; per default float
 * @tparam Format  format of the to be parsed object; per default
 *                 std::chars_format::general
 * @param str      object to be parsed
 * @return         floating point value of str
 */
template<
	typename Type = float,
	std::chars_format Format = std::chars_format::general,
	typename = std::enable_if_t<std::is_floating_point_v<Type>>>
[[nodiscard]] inline std::optional<Type> floating_point(const std::string_view& str);

/**
 * @brief custom parser for enumerations
 *
 * @note you pass a list of pairs that contain the values of the enumeration and
 * a string assigned to them
 *
 * @tparam Enum  name of the enum that is parsed
 * @return       the enum value which corresponds to the passed string or if
 *               none correspondes an optional
 */
template<typename Enum, typename = std::enable_if_t<std::is_enum_v<Enum>>>
class enumeration {
public:
	template<typename... Args>
	inline explicit enumeration(Args&&... args);

	/**
	 * @brief parses the object whether it fits an element of the enumeration and
	 * returns the element or an optional
	 *
	 * @param str  object that is parsed
	 * @return     the enum value which corresponds to the passed string or if
	 *             none correspondes an optional
	 */
	[[nodiscard]] inline std::optional<Enum> operator()(const std::string_view& str) const;

private:
	std::vector<std::pair<Enum, std::string_view>> m_name_value_pairs;
};

/**
 * @brief custom parser for lists
 *
 * @tparam T       type of the elements of the list
 * @tparam Parser  custom parser to parse the elements of the list
 * @return         vector that contains all the elements of the list
 */
template<typename T, typename Parser>
class list {
public:
	/**
	 *@brief Symbol used to delimit elements
	 */
	static constexpr auto separator = ',';

public:
	/**
	 * @brief sets the parser to parse the individual elements
	 *
	 * @param parser  parser to use for elements in the list
	 */
	inline explicit list(Parser&& parser);

	/**
	 * @brief parses the whole list and returns it in vector form
	 *
	 * @param str  object that is parsed
	 * @return     vector that contains all the elements of the list
	 */
	[[nodiscard]] inline std::optional<std::vector<T>> operator()(const std::string_view& str) const;

private:
	[[nodiscard]] inline std::optional<T> parse_value(const std::string_view& value_str) const;

private:
	Parser m_parse_value;
};

/**
 * @brief custom parser for lists that uses a default parser for the individual
 * elements
 *
 * @tparam T  type of list elements
 * @return    vector that contains the elements of the list
 */
template<typename T>
[[nodiscard]] inline list<T, arx_internal::default_parser> make_list();

/**
 * @brief custom parser for lists that uses a custom parser for the individual
 * elements
 *
 * @tparam T       type of list elements
 * @tparam Parser  custom parser to parse the individual elements of the list
 * @param parser   passed parser
 * @return         vector that contains the elements of the list
 */
template<typename T, typename Parser>
[[nodiscard]] inline list<T, Parser> make_list(Parser&& parser);

} // namespace arx_parsers

namespace arx_internal {

template<typename F, typename T>
struct is_parsing_function {
	static constexpr bool value = (std::is_same_v<std::invoke_result_t<F, std::string_view>, std::optional<T>>);
};

template<typename F, typename T>
constexpr bool is_parsing_function_v = is_parsing_function<F, T>::value;

template<typename... Ts>
constexpr inline bool is_unique(const Ts&... values) {

	auto value_array = std::array{ values... };

	bool sorted{};
	do {
		sorted = true;
		for (arx_ssize_t i = 1; i < arx_ssize_t(value_array.size()); ++i) {
			auto& a = value_array[i - 1];
			auto& b = value_array[i];
			if (a == b) {
				return false;
			} else if (b < a) {
				std::swap(a, b);
				sorted = false;
			}
		}
	} while (not sorted);

	return true;
}

template<arx_ssize_t Index, auto FlagID, class... Flags>
struct flag_index {};

template<arx_ssize_t Index, auto FlagID, typename T, typename Parser, class... Flags>
struct flag_index<Index, FlagID, flag<FlagID, T, Parser>, Flags...> {
	static constexpr arx_ssize_t value = Index;
};

template<arx_ssize_t Index, auto FlagID, class Flag, class... Flags>
struct flag_index<Index, FlagID, Flag, Flags...> {
	static constexpr arx_ssize_t value = flag_index<Index + 1, FlagID, Flags...>::value;
};

template<auto FlagID, class... Flags>
constexpr arx_ssize_t flag_index_v = flag_index<0, FlagID, Flags...>::value;

template<typename T>
constexpr inline bool is_floating_from_chars(...) {
	return false;
}

template<typename T>
constexpr inline bool is_floating_from_chars(
	std::from_chars_result (*const)(const char*, const char*, T&, std::chars_format) noexcept
) {
	return true;
}

} // namespace arx_internal

namespace arx_parsers_internal {

bool ends_with(const std::string_view& str, const std::string_view& suffix) {
	if (str.length() < suffix.length()) {
		return false;
	}
	return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

template<typename T>
std::optional<T> extract_number(const std::string_view& str, const std::string_view& suffix) {
	if (str.length() < suffix.length()) {
		return std::nullopt;
	}
	const auto num_str = str.substr(std::size_t(0), std::size_t(str.length() - suffix.length()));
	if constexpr (std::is_floating_point_v<T>) {
		return arx_parsers::floating_point<T>(num_str);
	} else {
		return arx_parsers::integer<T>(num_str);
	}
}

template<typename FromRep, class FromPeriod, class ToDuration>
std::optional<ToDuration> parse_time_from(const std::string_view& str, const std::string_view& suffix) {
	const auto number = extract_number<FromRep>(str, suffix);
	if (number.has_value()) {
		return std::chrono::duration_cast<ToDuration>(std::chrono::duration<FromRep, FromPeriod>(number.value()));
	}

	return std::nullopt;
}

template<typename T>
struct is_duration : std::false_type {};

template<typename Rep, class Period>
struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

template<typename T>
inline constexpr bool is_duration_v = is_duration<T>::value;

} // namespace arx_parsers_internal

namespace arx_parsers {

template<class Duration>
std::optional<Duration> time(const std::string_view& str) {

	if (arx_parsers_internal::ends_with(str, "h")) {
		return arx_parsers_internal::parse_time_from<double, std::ratio<3'600>, Duration>(str, "h");
	} else if (arx_parsers_internal::ends_with(str, "min")) {
		return arx_parsers_internal::parse_time_from<double, std::ratio<60>, Duration>(str, "min");
	} else if (arx_parsers_internal::ends_with(str, "s")) {
		return arx_parsers_internal::parse_time_from<double, std::ratio<1>, Duration>(str, "s");
	} else if (arx_parsers_internal::ends_with(str, "ms")) {
		return arx_parsers_internal::parse_time_from<std::uint64_t, std::milli, Duration>(str, "ms");
	} else if (arx_parsers_internal::ends_with(str, "ns")) {
		return arx_parsers_internal::parse_time_from<std::uint64_t, std::nano, Duration>(str, "ns");
	} else if (arx_parsers_internal::ends_with(str, "us")) {
		return arx_parsers_internal::parse_time_from<std::uint64_t, std::micro, Duration>(str, "us");
	}

	return std::nullopt;
}

template<typename Type, int Base, typename>
std::optional<Type> integer(const std::string_view& str) {
	Type value{};

	const auto [ptr, ec] = std::from_chars(str.begin(), str.end(), value, Base);
	if (ec == std::errc() and ptr == str.end()) {
		return value;
	}

	return std::nullopt;
}

template<typename Type, std::chars_format Format, typename>
std::optional<Type> floating_point(const std::string_view& str) {
	Type value{};

	// if constexpr (arx_internal::is_floating_from_chars<Type>(std::from_chars)) {
	//    const auto [ptr, ec] =
	//       std::from_chars(str.begin(), str.end(), value, Format);
	//   if (ec == std::errc() and ptr == str.end()) {
	//     return value;
	//   }
	// } else {
	const auto base = []() {
		switch (Format) {
		case std::chars_format::fixed:
			return std::fixed;
		case std::chars_format::hex:
			return std::hexfloat;
		default:
			return std::scientific;
		}
	}();

	auto parser = std::stringstream(std::string(str));
	if (parser >> base >> value) {
		return value;
	}
	// }
	return std::nullopt;
}

template<typename Enum, typename Enable>
template<typename... Args>
enumeration<Enum, Enable>::enumeration(Args&&... args) : m_name_value_pairs{ std::forward<Args>(args)... } {
}

template<typename Enum, typename Enable>
std::optional<Enum> enumeration<Enum, Enable>::operator()(const std::string_view& str) const {
	for (const auto& [value, name] : m_name_value_pairs) {
		if (name == str) {
			return value;
		}
	}
	return std::nullopt;
}

template<typename T, typename Parser>
list<T, Parser>::list(Parser&& parser) : m_parse_value{ std::forward<Parser>(parser) } {
}

template<typename T, typename Parser>
std::optional<T> list<T, Parser>::parse_value(const std::string_view& value_str) const {
	// Use custom parser if provided and if not try using a default parser.
	if constexpr (not std::is_same_v<Parser, arx_internal::default_parser>) {
		return std::invoke(m_parse_value, value_str);
	} else if constexpr (std::is_integral_v<T> && not std::is_same_v<T, bool>) {
		return arx_parsers::integer<T>(value_str);
	} else if constexpr (std::is_floating_point_v<T>) {
		return arx_parsers::floating_point<T>(value_str);
	} else if constexpr (std::is_same_v<std::string_view, T>) {
		return value_str;
	} else if constexpr (std::is_same_v<std::string, T>) {
		return std::string(value_str);
	} else if constexpr (std::is_same_v<std::filesystem::path, T>) {
		try {
			return std::filesystem::path(value_str);
		} catch (...) {
			// TODO consider warning
			return std::nullopt;
		}
	} else if constexpr (arx_parsers_internal::is_duration_v<T>) {
		return arx_parsers::time<T>(value_str);
	} else {
		T::__cannot_parse_this_type;
	}
}

template<typename T, typename Parser>
std::optional<std::vector<T>> list<T, Parser>::operator()(const std::string_view& str) const {

	const auto num_values = std::accumulate(str.begin(), str.end(), 1ull, [](const auto& count, const char& c) {
		return count + (c == separator);
	});

	std::vector<T> values;
	values.reserve(num_values);

	std::size_t begin_index = 0;
	while (true) {
		const auto end_index = str.find(separator, begin_index);
		auto value_opt = parse_value(str.substr(begin_index, end_index - begin_index));
		if (value_opt) {
			values.push_back(*value_opt);
		} else {
			// TODO consider adding a warning
		}
		if (end_index == std::string::npos) {
			break;
		}
		begin_index = end_index + sizeof(separator);
	}

	return values;
}

template<typename T>
list<T, arx_internal::default_parser> make_list() {
	return list<T, arx_internal::default_parser>(arx_internal::default_parser{});
}

template<typename T, typename Parser>
list<T, Parser> make_list(Parser&& parser) {
	return list<T, Parser>(std::forward<Parser>(parser));
}

} // namespace arx_parsers

template<auto Enum, typename T>
constexpr arx_internal::flag<Enum, T, arx_internal::default_parser> make_arx_flag(
	char short_name, std::string_view long_name
) {
	static_assert(std::is_enum_v<decltype(Enum)>, "Flag ID must have enum type.");
	return { short_name, long_name };
}

template<auto Enum, typename T>
constexpr arx_internal::flag<Enum, T, arx_internal::default_parser> make_arx_flag(std::string_view long_name) {
	return make_arx_flag<Enum, T>(arx_internal::no_short_flag, long_name);
}

template<auto Enum, typename T, typename Parser>
constexpr arx_internal::flag<Enum, T, Parser> make_arx_flag(
	char short_name, std::string_view long_name, Parser&& parser
) {
	static_assert(std::is_enum_v<decltype(Enum)>, "Flag ID must have enum type.");
	static_assert(
		arx_internal::is_parsing_function_v<Parser, T>,
		"Parser Function must satisfy 'is_parsing_function_v'."
	);
	return { short_name, long_name, std::forward<Parser>(parser) };
}

template<auto Enum, typename T, typename Parser>
constexpr arx_internal::flag<Enum, T, Parser> make_arx_flag(std::string_view long_name, Parser&& parser) {
	return make_arx_flag<Enum, T>(arx_internal::no_short_flag, long_name, std::forward<Parser>(parser));
}

template<typename... Flags>
template<typename Flag>
bool arx<Flags...>::matches_flag(char short_name, std::string_view long_name, std::string_view argument) {
	using namespace arx_internal;
	return (short_name != no_short_flag and argument.length() == short_flag_prefix.length() + sizeof(short_name) and
	        argument.substr(0, short_flag_prefix.length()) == short_flag_prefix and
	        argument[short_flag_prefix.length()] == short_name) or
		(argument.length() == long_flag_prefix.length() + long_name.length() and
	     argument.substr(0, long_flag_prefix.length()) == long_flag_prefix and
	     argument.substr(long_flag_prefix.length()) == long_name);
}

template<typename... Flags>
arx<Flags...>::arx(int num_args, const char* const * args, Flags&&... flags) :
	m_flags{ std::forward<Flags>(flags)... } {
	using namespace arx_internal;

	static_assert(is_unique(Flags::id...), "Flag IDs must be unique.");

	// Skip Program name
	for (int i = 1; i < num_args; ++i) {
		const auto argument = std::string_view{ args[i] };

		bool is_bool_flag;
		arx_ssize_t flag_index = -1;

		const auto found_match = std::apply(
			[&](const Flags&... flag_config) {
				return (
					(++flag_index,
			         is_bool_flag = std::is_same_v<typename Flags::type, bool>,
			         matches_flag<Flags>(flag_config.short_name, flag_config.long_name, argument)) or
					...
				);
			},
			m_flags
		);

		if (found_match) {
			if (is_bool_flag) {
				m_bound_arguments.emplace_back(flag_index, argument);
			} else {
				if (i + 1 < num_args) {
					++i;
					m_bound_arguments.emplace_back(flag_index, std::string_view{ args[i] });
				}
			}
		} else {
			m_unbound_arguments.emplace_back(argument);
		}
	}

	// Sort arguments in ascending order by flag id without changing order for
	// duplicates.
	std::stable_sort(
		m_bound_arguments.begin(),
		m_bound_arguments.end(),
		[](const bound_argument& a, const bound_argument& b) {
			// For some reason '<' confuses clang 16.
			return std::less<arx_ssize_t>{}(a.flag_index, b.flag_index);
		}
	);

	// Only store last duplicate.
	const auto last = std::unique(
						  m_bound_arguments.rbegin(),
						  m_bound_arguments.rend(),
						  [](const bound_argument& a, const bound_argument& b) { return a.flag_index == b.flag_index; }
	).base();

	m_bound_arguments.erase(m_bound_arguments.begin(), last);
}

template<class... Flags>
std::optional<std::string_view> arx<Flags...>::find_flag_value(arx_ssize_t flag_index) const {
	// Binary search through flag IDs.
	const auto it = std::lower_bound(
		m_bound_arguments.begin(),
		m_bound_arguments.end(),
		flag_index,
		[](const bound_argument& a, const arx_ssize_t& index) { return a.flag_index < index; }
	);
	if (it != m_bound_arguments.end() and it->flag_index == flag_index) {
		return { it->value };
	}
	return std::nullopt;
}

template<class... Flags>
template<class Flag>
std::optional<typename Flag::type> arx<Flags...>::parse_value(Flag& flag, const std::string_view& value_str) const {

	using Type = typename Flag::type;

	// Use custom parser if provided and if not try using a default parser.
	if constexpr (not std::is_same_v<decltype(Flag::parse), std::nullptr_t>) {
		return std::invoke(flag.parse, value_str);
	} else if constexpr (std::is_integral_v<Type> && not std::is_same_v<Type, bool>) {
		return arx_parsers::integer<Type>(value_str);
	} else if constexpr (std::is_floating_point_v<Type>) {
		return arx_parsers::floating_point<Type>(value_str);
	} else if constexpr (std::is_same_v<std::string_view, Type>) {
		return value_str;
	} else if constexpr (std::is_same_v<std::string, Type>) {
		return std::string(value_str);
	} else if constexpr (std::is_same_v<std::filesystem::path, Type>) {
		try {
			return std::filesystem::path(value_str);
		} catch (...) {
			// TODO consider warning
			return std::nullopt;
		}
	} else if constexpr (arx_parsers_internal::is_duration_v<Type>) {
		return arx_parsers::time<Type>(value_str);
	} else {
		Type::__cannot_parse_this_type;
	}

	return std::nullopt;
}

template<class... Flags>
template<auto FlagID>
auto arx<Flags...>::get() const {
	using namespace arx_internal;

	static constexpr auto flag_index = flag_index_v<FlagID, Flags...>;
	using Flag = std::tuple_element_t<flag_index, flag_tuple_t>;
	using Type = typename Flag::type;
	using opt_t = std::optional<Type>;

	const auto value_opt = find_flag_value(flag_index);
	if constexpr (std::is_same_v<Type, bool>) {
		return opt_t{ value_opt.has_value() };
	} else if (value_opt) {
		return opt_t{ parse_value(std::get<flag_index>(m_flags), *value_opt) };
	}

	return opt_t{ std::nullopt };
}

template<class... Flags>
inline const std::vector<std::string_view>& arx<Flags...>::get_positionals() const {
	return m_unbound_arguments;
}
