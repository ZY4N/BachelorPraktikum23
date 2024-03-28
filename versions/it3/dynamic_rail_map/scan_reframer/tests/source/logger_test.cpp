#include "gtest/gtest.h"
#include "logger_test_util.hpp"
#include <bitset>


template<typename... Ts, typename... Us>
void test_error(
	std::tuple<Ts...> logger_args,
	std::tuple<Us...> emulate_args,
	const logger::level threshold = logger::level::generic
) {
	const auto emulated_error_string = std::apply(
		[&](auto&& ... args) {
			return emulate_error(args...);
		}, emulate_args
	);
	const auto logger_error_string = std::apply(
		[&](auto&& ... args) {
			return error_to_string(threshold, args...);
		}, logger_args
	);
	ASSERT_EQ(emulated_error_string, logger_error_string);
}

template<typename... Ts, typename... Us>
void test_warn(
	std::tuple<Ts...> logger_args,
	std::tuple<Us...> emulate_args,
	const logger::level threshold = logger::level::generic
) {
	const auto emulated_warn_string = std::apply(
		[&](auto&& ... args) {
			return emulate_warn(args...);
		}, emulate_args
	);
	const auto logger_warn_string = std::apply(
		[&](auto&& ... args) {
			return warn_to_string(threshold, args...);
		}, logger_args
	);
	ASSERT_EQ(emulated_warn_string, logger_warn_string);
}

template<typename... Ts, typename... Us>
void test_info(
	std::tuple<Ts...> logger_args,
	std::tuple<Us...> emulate_args,
	const logger::level threshold = logger::level::generic
) {
	const auto emulated_info_string = std::apply(
		[&](auto&& ... args) {
			return emulate_info(args...);
		}, emulate_args
	);
	const auto logger_info_string = std::apply(
		[&](auto&& ... args) {
			return info_to_string(threshold, args...);
		}, logger_args
	);
	ASSERT_EQ(emulated_info_string, logger_info_string);
}

template<typename... Ts, typename... Us>
void test_log(
	std::tuple<Ts...> logger_args,
	std::tuple<Us...> emulate_args,
	const logger::level threshold = logger::level::generic
) {
	const auto emulated_log_string = std::apply(
		[&](auto&& ... args) {
			return emulate_log(args...);
		}, emulate_args
	);
	const auto logger_log_string = std::apply(
		[&](auto&& ... args) {
			return log_to_string(threshold, args...);
		}, logger_args
	);
	ASSERT_EQ(emulated_log_string, logger_log_string);
}

template<typename... Ts, typename... Us>
void test_debug(
	std::tuple<Ts...> logger_args,
	std::tuple<Us...> emulate_args,
	const logger::level threshold = logger::level::generic
) {
	const auto emulated_debug_string = std::apply(
		[&](auto&& ... args) {
			return emulate_debug(args...);
		}, emulate_args
	);
	const auto logger_debug_string = std::apply(
		[&](auto&& ... args) {
			return debug_to_string(threshold, args...);
		}, logger_args
	);
	ASSERT_EQ(emulated_debug_string, logger_debug_string);
}

template<typename... Ts, typename... Us>
void test_all_levels(std::tuple<Ts...> logger_args, std::tuple<Us...> emulate_args) {
	test_error(logger_args, emulate_args);
	test_warn(logger_args, emulate_args);
	test_info(logger_args, emulate_args);
	test_log(logger_args, emulate_args);
	test_debug(logger_args, emulate_args);
}

TEST(logger_test, format_only_text) {
	test_all_levels(
		std::make_tuple("Hello World"),
		std::make_tuple("Hello World")
	);
}

TEST(logger_test, format_only_value) {
	test_all_levels(
		std::make_tuple("%", 8),
		std::make_tuple(make_arg_value(8))
	);
}

TEST(logger_test, format_value_in_text) {
	test_all_levels(
		std::make_tuple("The number % is particularly nice!", 8),
		std::make_tuple("The number ", make_arg_value(8), " is particularly nice!")
	);
}

TEST(logger_test, format_value_at_end_of_text) {
	test_all_levels(
		std::make_tuple("My favourite number is: %", 8),
		std::make_tuple("My favourite number is: ", make_arg_value(8))
	);
}

TEST(logger_test, format_value_at_begin_of_text) {
	test_all_levels(
		std::make_tuple("% has always been my favourite number.", 8),
		std::make_tuple(make_arg_value(8), " has always been my favourite number.")
	);
}

TEST(logger_test, format_values_without_separators) {
	test_all_levels(
		std::make_tuple("But I also like %%.", 4, 2),
		std::make_tuple("But I also like ", make_arg_value(4), make_arg_value(2), ".")
	);
}

TEST(logger_test, format_allows_ios_parameters) {
	test_all_levels(
		std::make_tuple("This includes 0x%% 0o%% and 0b%.", std::hex, 42, std::oct, 42, std::bitset<32>{ 42 }),
		std::make_tuple(
			"This includes 0x", make_arg_value(std::hex), make_arg_value(42),
			" 0o", make_arg_value(std::oct), make_arg_value(42),
			" and 0b", make_arg_value(std::bitset<32>{ 42 }),
			"."
		)
	);
}

TEST(logger_test, format_allows_line_break) {
	test_all_levels(
		std::make_tuple("This test requires a\nnew line!"),
		std::make_tuple("This test requires a\nnew line!")
	);
}

TEST(logger_test, log_level_threshold_debug) {
	const auto text = "Hello World";
	const auto threshold = logger::level::debug;
	ASSERT_EQ(error_to_string(threshold, text), emulate_error(text));
	ASSERT_EQ(warn_to_string(threshold, text), emulate_warn(text));
	ASSERT_EQ(info_to_string(threshold, text), emulate_info(text));
	ASSERT_EQ(log_to_string(threshold, text), emulate_log(text));
	ASSERT_EQ(debug_to_string(threshold, text), emulate_debug(text));
}

TEST(logger_test, log_level_threshold_log) {
	const auto text = "Hello World";
	const auto threshold = logger::level::log;
	ASSERT_EQ(error_to_string(threshold, text), emulate_error(text));
	ASSERT_EQ(warn_to_string(threshold, text), emulate_warn(text));
	ASSERT_EQ(info_to_string(threshold, text), emulate_info(text));
	ASSERT_EQ(log_to_string(threshold, text), emulate_log(text));
	ASSERT_EQ(debug_to_string(threshold, text), "");
}

TEST(logger_test, log_level_threshold_info) {
	const auto text = "Hello World";
	const auto threshold = logger::level::info;
	ASSERT_EQ(error_to_string(threshold, text), emulate_error(text));
	ASSERT_EQ(warn_to_string(threshold, text), emulate_warn(text));
	ASSERT_EQ(info_to_string(threshold, text), emulate_info(text));
	ASSERT_EQ(log_to_string(threshold, text), "");
	ASSERT_EQ(debug_to_string(threshold, text), "");

}

TEST(logger_test, log_level_threshold_warn) {
	const auto text = "Hello World";
	const auto threshold = logger::level::warn;
	ASSERT_EQ(error_to_string(threshold, text), emulate_error(text));
	ASSERT_EQ(warn_to_string(threshold, text), emulate_warn(text));
	ASSERT_EQ(info_to_string(threshold, text), "");
	ASSERT_EQ(log_to_string(threshold, text), "");
	ASSERT_EQ(debug_to_string(threshold, text), "");
}

TEST(logger_test, log_level_threshold_error) {
	const auto text = "Hello World";
	const auto threshold = logger::level::error;
	ASSERT_EQ(error_to_string(threshold, text), emulate_error(text));
	ASSERT_EQ(warn_to_string(threshold, text), "");
	ASSERT_EQ(info_to_string(threshold, text), "");
	ASSERT_EQ(log_to_string(threshold, text), "");
	ASSERT_EQ(debug_to_string(threshold, text), "");
}

TEST(logger_test, log_level_threshold_mute) {
	const auto text = "Hello World";
	const auto threshold = logger::level::mute;
	ASSERT_EQ(error_to_string(threshold, text), "");
	ASSERT_EQ(warn_to_string(threshold, text), "");
	ASSERT_EQ(info_to_string(threshold, text), "");
	ASSERT_EQ(log_to_string(threshold, text), "");
	ASSERT_EQ(debug_to_string(threshold, text), "");
}
