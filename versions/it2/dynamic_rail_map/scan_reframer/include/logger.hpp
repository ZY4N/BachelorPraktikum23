#pragma once

#include <array>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <string_view>
#include <cinttypes>

/**
 * @brief A lightweight logging library providing color-coded output and flexible configuration.
 *
 * @details This namespace serves as a wrapper around std::ostream, offering a simple yet powerful
 * logging interface with support for ANSI color-coded log levels. It provides a global logging instance
 * as well as customizable logger instances, allowing users to configure output streams, log levels, and
 * easily integrates logging into their applications.
 */
namespace logger {

//--------------[ declarations ]--------------//

/**
 * @brief Placeholder symbol used in format strings to signal value position.
 */
static constexpr char fmt_symbol = '%';

/**
 * @brief Enumeration representing the log levels.
 *
 * The log levels are ordered from least verbose to most verbose, as follows:
 * - @c mute:	 Indicates that no log messages should be emitted.
 * - @c error:   Used for critical errors that require immediate attention.
 * - @c warn:	 Used for potential issues that may need attention.
 * - @c info:	 Used for significant events and information about the process.
 * - @c log:	 General log messages providing information about the application's operation.
 * - @c debug:   Detailed debug information helpful for troubleshooting.
 * - @c generic: A catch-all level for generic log messages.
 */
enum class level : std::uint8_t {
	mute = 0,
	error = 1,
	warn = 2,
	info = 3,
	log = 4,
	debug = 5,
	generic = 6
};


//--------------[ global logger ]--------------//

class instance;

/**
 * @return A reference to the @c global_instance.
 */
inline instance& global_instance();

/**
 * @brief Sets the log @c level of the @c global_instance.
 */
inline void set_global_level(level);

/**
 * @return The log level currently used by the @c global_instance.
 */
[[nodiscard]] inline level get_global_level();

/**
 * @brief Sets the output stream used by the @c global_instance for regular log messages.
 *
 * This function sets the output stream to which the @c global_instance
 * writes messages of the following types:
 * - @c info
 * - @c log
 * - @c debug
 * - @c generic
 *
 * By default, these message types are directed to the standard output (@c std::cout).
 *
 * @param out A reference to an @c std::ostream instance.
 */
inline void set_global_out(std::ostream& out);

/**
 * @brief Returns the global @c std::ostream for regular log messages.
 */
[[nodiscard]] inline std::ostream& get_global_out();


/**
 * @brief Sets the output stream used by the @c global_instance for error log messages.
 *
 * This function sets the output stream to which the @c global_instance
 * writes messages of the following types:
 * - @c error
 * - @c warn
 *
 * By default, these message types are directed to the standard error output (@c std::cerr).
 *
 * @param err A reference to an @c std::ostream instance.
 */
inline void set_global_err(std::ostream& err);

/**
 * @brief Returns the global output stream for error log messages.
 */
[[nodiscard]] inline std::ostream& get_global_err();

/**
 * @brief Formats and logs an error message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the format string.
 * @param fmt   The format string for the error message, supporting placeholders.
 * @param args  The values to be formatted and included in the error message.
 *
 * @note Extra placeholders or values are ignored.
 */
template<typename... Args>
inline void error(std::string_view fmt, Args&& ... args);

/**
 * @brief Formats and logs a warning message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the format string.
 * @param fmt   The format string for the warn message, supporting placeholders.
 * @param args  The values to be formatted and included in the warn message.
 *
 * @note Extra placeholders or values are ignored.
 */
template<typename... Args>
inline void warn(std::string_view fmt, Args&& ... args);

/**
 * @brief Formats and logs an info message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the format string.
 * @param fmt   The format string for the info message, supporting placeholders.
 * @param args  The values to be formatted and included in the info message.
 *
 * @note Extra placeholders or values are ignored.
 */
template<typename... Args>
inline void info(std::string_view fmt, Args&& ... args);

/**
 * @brief Formats and logs a log message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the format string.
 * @param fmt   The format string for the log message, supporting placeholders.
 * @param args  The values to be formatted and included in the log message.
 *
 * @note Extra placeholders or values are ignored.
 */
template<typename... Args>
inline void log(std::string_view fmt, Args&& ... args);

/**
 * @brief Formats and logs a debug message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the format string.
 * @param fmt   The format string for the debug message, supporting placeholders.
 * @param args  The values to be formatted and included in the debug message.
 *
 * @note Extra placeholders or values are ignored.
 */
template<typename... Args>
inline void debug(std::string_view fmt, Args&& ... args);

/**
 * @brief  Formats and logs a message to the given @c std::ostream.
 *
 * Handles the formatting of a log message based on the provided log level,
 * evaluates whether it meets the specified threshold level, and writes the
 * formatted message to the given @c std::ostream.
 *
 * @tparam Args	 Variadic template for the types of arguments passed to the format string.
 * @param out	   The @c std::ostream to which the formatted message will be written.
 * @param log_level The log @c level of the message being logged.
 * @param threshold Messages below this level will be ignored.
 * @param format	The format string for the message, supporting placeholders.
 * @param args	  The values to be formatted and included in the message.
 */
template<typename... Args>
inline void println(
	std::ostream& out,
	logger::level log_level,
	logger::level threshold,
	const std::string_view& format,
	Args&& ... args
);


//--------------[ logger instance ]--------------//

/**
 * @brief Configurable logger instance for customizing logging parameters.
 *
 * The @c instance class allows the configuration of logging parameters,
 * such as output streams and log levels, without affecting the global
 * logging instance. This provides a flexible way to control logging
 * behavior within specific scopes or components.
 */
class instance {
public:
	/**
	 * @brief Constructs a logger instance with optional parameters.
	 *
	 * @param n_out   Custom output stream for log messages.
	 * @param n_err   Custom error stream for log messages.
	 * @param n_level Custom log level for the instance.
	 */
	inline explicit instance(
		std::ostream& n_out = get_global_out(),
		std::ostream& n_err = get_global_err(),
		logger::level n_level = get_global_level()
	);

	/**
	 * @brief Set the log level for the instance.
	 * @param new_level the new log @c level
	 */
	inline void set_level(level new_level);

	/**
	 * @return The current log level of the instance.
	 */
	[[nodiscard]] inline level get_level() const;

	/**
	 * @brief Sets the output stream used by the @c instance for regular log messages.
	 */
	inline void set_out(std::ostream&);

	/**
	 * @return The current output stream of the instance.
	 */
	[[nodiscard]] inline std::ostream& get_out() const;

	/**
	 * @brief Sets the output stream used by the @c instance for error log messages.
	 */
	inline void set_err(std::ostream&);

	/**
	 * @return The current error stream of the instance.
	 */
	[[nodiscard]] inline std::ostream& get_err() const;

	/**
	 * @brief Formats and logs an error message to the instances error stream.
	 *
	 * The format string may contain placeholders (@c fmt_symbol)
	 * replaced by corresponding values provided in the arguments (@c args).
	 *
	 * @tparam Args Variadic template for the types of arguments passed to the format string.
	 * @param fmt   The format string for the error message, supporting placeholders.
	 * @param args  The values to be formatted and included in the error message.
	 *
	 * @note Extra placeholders or values are ignored.
	 */
	template<typename... Args>
	inline void error(std::string_view fmt, Args&& ... args) const;

	/**
	 * @brief Formats and logs a warning message to the instances error stream.
	 *
	 * The format string may contain placeholders (@c fmt_symbol)
	 * replaced by corresponding values provided in the arguments (@c args).
	 *
	 * @tparam Args Variadic template for the types of arguments passed to the format string.
	 * @param fmt   The format string for the warning message, supporting placeholders.
	 * @param args  The values to be formatted and included in the warning message.
	 *
	 * @note Extra placeholders or values are ignored.
	 */
	template<typename... Args>
	inline void warn(std::string_view fmt, Args&& ... args) const;

	/**
	 * @brief Formats and logs an info message to the instances output stream.
	 *
	 * The format string may contain placeholders (@c fmt_symbol)
	 * replaced by corresponding values provided in the arguments (@c args).
	 *
	 * @tparam Args Variadic template for the types of arguments passed to the format string.
	 * @param fmt   The format string for the info message, supporting placeholders.
	 * @param args  The values to be formatted and included in the info message.
	 *
	 * @note Extra placeholders or values are ignored.
	 */
	template<typename... Args>
	inline void info(std::string_view fmt, Args&& ... args) const;

	/**
	 * @brief Formats and logs a log message to the instances output stream.
	 *
	 * The format string may contain placeholders (@c fmt_symbol)
	 * replaced by corresponding values provided in the arguments (@c args).
	 *
	 * @tparam Args Variadic template for the types of arguments passed to the format string.
	 * @param fmt   The format string for the log message, supporting placeholders.
	 * @param args  The values to be formatted and included in the log message.
	 *
	 * @note Extra placeholders or values are ignored.
	 */
	template<typename... Args>
	inline void log(std::string_view fmt, Args&& ... args) const;

	/**
	 * @brief Formats and logs a debug message to the instances output stream.
	 *
	 * The format string may contain placeholders (@c fmt_symbol)
	 * replaced by corresponding values provided in the arguments (@c args).
	 *
	 * @tparam Args Variadic template for the types of arguments passed to the format string.
	 * @param fmt   The format string for the debug message, supporting placeholders.
	 * @param args  The values to be formatted and included in the debug message.
	 *
	 * @note Extra placeholders or values are ignored.
	 */
	template<typename... Args>
	inline void debug(std::string_view fmt, Args&& ... args) const;

private:
	std::ostream* m_out;
	std::ostream* m_err;
	level m_level;
};

} // namespace logger


//--------------[ logger_internal implementation ]--------------//

namespace logger_internal {

enum class colors : std::uint8_t {
	reset = 0,
	black = 30,
	red = 31,
	green = 32,
	yellow = 33,
	blue = 34,
	magenta = 35,
	cyan = 36,
	white = 37
};

inline constexpr std::size_t num_digits(std::uint32_t n, std::uint32_t base = 10) {
	if (n < base) {
		return 1;
	}
	std::size_t digits = 0;
	while (n > 0) {
		n /= base;
		digits++;
	}
	return digits;
}

template<std::uint32_t N, std::uint32_t B = 10>
inline constexpr auto int_to_str() {
	auto str = std::array<char, num_digits(N, B)>{};

	auto index = str.size() - 1;
	auto num = N;
	do {
		str[index] = (char)('0' + num % B);
		num /= B;
	} while (index--);

	return str;
}

template<colors color, bool bright>
inline constexpr auto create_ansi_color() {

	constexpr auto color_index = static_cast<std::uint8_t>(color);
	constexpr auto color_index_str = int_to_str<color_index>();

	constexpr auto prefix = std::string_view("\x1B[");
	constexpr auto postfix = [&]() -> std::string_view {
		if constexpr (bright) {
			return ";1m";
		} else {
			return "m";
		}
	}();

	constexpr auto color_str_length = (
		prefix.size() +
			color_index_str.size() +
			postfix.size()
	);
	std::array<char, color_str_length> color_str{};

	auto it = color_str.begin();
	const auto append = [&it](auto begin, auto end) {
		while (begin != end) {
			*it++ = *begin++;
		}
	};

	append(prefix.begin(), prefix.end());
	append(color_index_str.begin(), color_index_str.end());
	append(postfix.begin(), postfix.end());

	return color_str;
}

inline static constexpr auto reset_color = create_ansi_color<colors::reset, false>();

struct color_string {
	colors color;
	std::string_view name;
};

inline static constexpr std::array<color_string, 6> colored_level_names{
	color_string{ colors::red, "error" },
	color_string{ colors::yellow, "warning" },
	color_string{ colors::magenta, "info" },
	color_string{ colors::white, "log" },
	color_string{ colors::blue, "debug" },
	color_string{ colors::white, "generic" }
};


inline constexpr auto max_colored_level_name_length = std::max_element(
	colored_level_names.begin(), colored_level_names.end(),
	[](const auto& a, const auto& b) {
		return a.name.size() < b.name.size();
	}
)->name.size();


template<colors Color>
inline constexpr auto create_prefix(std::string_view name) {
	constexpr auto color_str = logger_internal::create_ansi_color<Color, true>();

	constexpr auto prefix_length = (
		sizeof('[') +
			color_str.size() +
			max_colored_level_name_length + sizeof(' ') +
			logger_internal::reset_color.size() +
			sizeof(']')
	);

	std::array<char, prefix_length> prefix{};

	auto it = prefix.begin();
	const auto append = [&it](auto begin, auto end) {
		while (begin != end) {
			*it++ = *begin++;
		}
	};

	*it++ = '[';
	append(color_str.begin(), color_str.end());
	append(name.begin(), name.end());
	append(logger_internal::reset_color.begin(), logger_internal::reset_color.end());
	*it++ = ']';

	while (it != prefix.end()) {
		*it++ = ' ';
	}

	return prefix;
}

template<auto... Is>
inline constexpr auto create_color_prefix_tuple(std::index_sequence<Is...>) {
	return std::tuple{
		std::pair{
			create_ansi_color<colored_level_names[Is].color, false>(),
			create_prefix<colored_level_names[Is].color>(colored_level_names[Is].name)
		}...
	};
}

inline constexpr auto color_prefix_tuple = create_color_prefix_tuple(
	std::make_index_sequence<colored_level_names.size()>{}
);

template<auto... Is>
inline constexpr auto create_color_prefix_lookup(std::index_sequence<Is...>) {
	return std::array{
		std::pair{
			std::string_view(
				std::get<Is>(color_prefix_tuple).first.data(),
				std::get<Is>(color_prefix_tuple).first.size()
			),
			std::string_view(
				std::get<Is>(color_prefix_tuple).second.data(),
				std::get<Is>(color_prefix_tuple).second.size()
			)
		}...
	};
}

inline constexpr auto color_prefix_lookup = create_color_prefix_lookup(
	std::make_index_sequence<colored_level_names.size()>{}
);

inline void print_impl(
	std::ostream& out,
	std::string_view,
	std::string_view format
) {
	out << format;
}

template<typename First, typename... Rest>
inline void print_impl(
	std::ostream& out,
	std::string_view color,
	std::string_view format,
	First&& first,
	Rest&& ... rest
) {
	if (format.empty()) {
		return;
	}
	const auto next_index = format.find(logger::fmt_symbol);
	if (next_index == std::string::npos) {
		out << format;
	} else {
		out.write(format.data(), static_cast<std::streamsize>(next_index));
		out.write(color.data(), static_cast<std::streamsize>(color.size()));
		out << std::forward<First>(first);
		out.write(
			logger_internal::reset_color.data(), static_cast<std::streamsize>(logger_internal::reset_color.size())
		);
		print_impl(out, color, format.substr(next_index + sizeof(logger::fmt_symbol)), std::forward<Rest>(rest)...);
	}
}

} // namespace logger_internal


namespace logger {

//--------------[ instance implementation ]--------------//

instance::instance(
	std::ostream& n_out,
	std::ostream& n_err,
	logger::level n_level
) : m_out{ &n_out }, m_err{ &n_err }, m_level{ n_level } {
}

void instance::set_level(level new_level) {
	m_level = new_level;
}

level instance::get_level() const {
	return m_level;
}

void instance::set_out(std::ostream& new_out) {
	m_out = &new_out;
}

std::ostream& instance::get_out() const {
	return *m_out;
}

void instance::set_err(std::ostream& new_err) {
	m_err = &new_err;
}

std::ostream& instance::get_err() const {
	return *m_err;
}


template<typename... Args>
void println(
	std::ostream& out,
	level log_level,
	level threshold,
	const std::string_view& format,
	Args&& ... args
) {
	auto log_level_index = static_cast<std::uint8_t>(log_level);
	const auto threshold_index = static_cast<std::uint8_t>(threshold);
	if (log_level_index <= threshold_index) {
		log_level_index = std::min(log_level_index, static_cast<std::uint8_t>(logger::level::generic)) - 1;
		const auto [color, prefix] = logger_internal::color_prefix_lookup[log_level_index];
		out << prefix;
		logger_internal::print_impl(out, color, format, std::forward<Args>(args)...);
		out << std::endl;
	}
}

template<typename... Args>
void instance::error(std::string_view fmt, Args&& ... args) const {
	println(*m_err, level::error, m_level, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void instance::warn(std::string_view fmt, Args&& ... args) const {
	println(*m_err, level::warn, m_level, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void instance::info(std::string_view fmt, Args&& ... args) const {
	println(*m_out, level::info, m_level, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void instance::log(std::string_view fmt, Args&& ... args) const {
	println(*m_out, level::log, m_level, fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void instance::debug(std::string_view fmt, Args&& ... args) const {
	println(*m_out, level::debug, m_level, fmt, std::forward<Args>(args)...);
}


//--------------[ global logger implementation ]--------------//

instance& global_instance() {
	static auto the_global_instance = instance(
		std::cout, std::cerr, level::generic
	);
	return the_global_instance;
}

void set_global_level(level new_level) {
	global_instance().set_level(new_level);
}

level get_global_level() {
	return global_instance().get_level();
}

void set_global_out(std::ostream& new_out) {
	global_instance().set_out(new_out);
}

std::ostream& get_global_out() {
	return global_instance().get_out();
}

void set_global_err(std::ostream& new_err) {
	global_instance().set_err(new_err);
}

std::ostream& get_global_err() {
	return global_instance().get_err();
}

template<typename... Args>
void error(std::string_view fmt, Args&& ... args) {
	global_instance().error(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void warn(std::string_view fmt, Args&& ... args) {
	global_instance().warn(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void info(std::string_view fmt, Args&& ... args) {
	global_instance().info(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void log(std::string_view fmt, Args&& ... args) {
	global_instance().log(fmt, std::forward<Args>(args)...);
}

template<typename... Args>
void debug(std::string_view fmt, Args&& ... args) {
	global_instance().debug(fmt, std::forward<Args>(args)...);
}

} // namespace logger