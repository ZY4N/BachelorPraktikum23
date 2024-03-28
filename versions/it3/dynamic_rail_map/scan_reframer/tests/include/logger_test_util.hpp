#pragma once

#include "util/logger.hpp"

#include <sstream>
#include <string>
#include <utility>

namespace ansi_colors {

static constexpr auto reset = "\u001b[0m";

static constexpr auto red = "\u001b[31m";
static constexpr auto yellow = "\u001b[33m";
static constexpr auto blue = "\u001b[34m";
static constexpr auto magenta = "\u001b[35m";
static constexpr auto white = "\u001b[37m";

static constexpr auto light_red = "\u001b[31;1m";
static constexpr auto light_yellow = "\u001b[33;1m";
static constexpr auto light_blue = "\u001b[34;1m";
static constexpr auto light_magenta = "\u001b[35;1m";
static constexpr auto light_white = "\u001b[37;1m";

} // namespace ansi_colors

template<typename... Args>
std::string println_to_string(
	const logger::level threshold,
	void (logger::instance::*set_out_func)(std::ostream&),
	void (logger::instance::*log_func)(std::string_view, Args&&...) const,
	const std::string_view fmt,
	Args&&... args
) {
	std::stringstream out{};
	logger::instance instance{};
	instance.set_level(threshold);
	(instance.*set_out_func)(out);
	(instance.*log_func)(fmt, std::forward<Args>(args)...);
	return out.str();
}

template<typename... Args>
std::string error_to_string(const logger::level threshold, const std::string_view fmt, Args&&... args) {
	return println_to_string(
		threshold,
		&logger::instance::set_err,
		&logger::instance::error,
		fmt,
		std::forward<Args>(args)...
	);
}

template<typename... Args>
std::string warn_to_string(const logger::level threshold, const std::string_view fmt, Args&&... args) {
	return println_to_string(
		threshold,
		&logger::instance::set_err,
		&logger::instance::warn,
		fmt,
		std::forward<Args>(args)...
	);
}

template<typename... Args>
std::string info_to_string(const logger::level threshold, const std::string_view fmt, Args&&... args) {
	return println_to_string(
		threshold,
		&logger::instance::set_out,
		&logger::instance::info,
		fmt,
		std::forward<Args>(args)...
	);
}

template<typename... Args>
std::string log_to_string(const logger::level threshold, const std::string_view fmt, Args&&... args) {
	return println_to_string(
		threshold,
		&logger::instance::set_out,
		&logger::instance::log,
		fmt,
		std::forward<Args>(args)...
	);
}

template<typename... Args>
std::string debug_to_string(const logger::level threshold, const std::string_view fmt, Args&&... args) {
	return println_to_string(
		threshold,
		&logger::instance::set_out,
		&logger::instance::debug,
		fmt,
		std::forward<Args>(args)...
	);
}

template<typename T>
struct arg_value {
	T value;
};

template<typename T>
struct is_arg_value : std::false_type {};

template<typename T>
struct is_arg_value<arg_value<T>> : std::true_type {};

template<typename T>
arg_value<T> make_arg_value(T&& value) {
	return { std::forward<T>(value) };
}

template<typename T>
void format_value(std::ostream& out, std::string_view color, T&& arg) {
	if constexpr (is_arg_value<std::remove_cv_t<std::remove_reference_t<T>>>::value) {
		out << color << arg.value << ansi_colors::reset;
	} else {
		out << arg;
	}
}

template<typename... Args>
std::string emulate_println(
	const std::string_view light_color,
	const std::string_view normal_color,
	const std::string_view name,
	const std::string_view padding,
	Args&&... args
) {
	std::stringstream out{};
	out << "[" << light_color << name << ansi_colors::reset << "]" << padding;
	(format_value(out, normal_color, std::forward<Args>(args)), ...);
	out << std::endl;
	return out.str();
}

template<typename... Args>
std::string emulate_error(Args&&... args) {
	return emulate_println(ansi_colors::light_red, ansi_colors::red, "error", "   ", std::forward<Args>(args)...);
}

template<typename... Args>
std::string emulate_warn(Args&&... args) {
	return emulate_println(ansi_colors::light_yellow, ansi_colors::yellow, "warning", " ", std::forward<Args>(args)...);
}

template<typename... Args>
std::string emulate_info(Args&&... args) {
	return emulate_println(
		ansi_colors::light_magenta,
		ansi_colors::magenta,
		"info",
		"    ",
		std::forward<Args>(args)...
	);
}

template<typename... Args>
std::string emulate_log(Args&&... args) {
	return emulate_println(ansi_colors::light_white, ansi_colors::white, "log", "     ", std::forward<Args>(args)...);
}

template<typename... Args>
std::string emulate_debug(Args&&... args) {
	return emulate_println(ansi_colors::light_blue, ansi_colors::blue, "debug", "   ", std::forward<Args>(args)...);
}
