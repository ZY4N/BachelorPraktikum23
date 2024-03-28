#include "config/types.hpp"
#include "util/arx.hpp"

#include "gtest/gtest.h"

enum class args {
	boolean,
	integer,
	unsigned_long,
	floating,
	double_precision,
	enumeration,
	string_list,
	integer_list,
	double_list,
	path,
	time,
	exists
};

enum class my_enum {
	one,
	two,
	three
};

TEST(arx, test_all_with_no_arguments) {
	const auto my_arx = arx(
		0,
		nullptr,
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(false, my_arx.template get<args::boolean>().value());
	ASSERT_EQ(false, my_arx.template get<args::integer>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::unsigned_long>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::floating>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::double_precision>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::enumeration>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::string_list>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::integer_list>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::double_list>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::path>().has_value());
	ASSERT_EQ(false, my_arx.template get<args::time>().has_value());
	ASSERT_EQ(true, my_arx.get_positionals().empty());
}

TEST(arx, test_all_with_all_flags) {
	static constexpr auto args = std::array{ "scan_combiner",
		                                     "--bool",
		                                     "hello",
		                                     "this",
		                                     "--integer",
		                                     "42",
		                                     "is",
		                                     "a",
		                                     "test",
		                                     "--enum",
		                                     "three",
		                                     "--string_list",
		                                     "abc,defg",
		                                     "--unsigned_long",
		                                     "380",
		                                     "--float",
		                                     "42",
		                                     "--double",
		                                     "1.8",
		                                     "--integer_list",
		                                     "1,2,3",
		                                     "--double_list",
		                                     "2.1,3.2",
		                                     "-p",
		                                     "../../",
		                                     "-t",
		                                     "4min",
		                                     "!" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(true, my_arx.template get<args::boolean>().value_or(false));
	ASSERT_EQ(42, my_arx.template get<args::integer>().value_or(0));
	ASSERT_EQ(380, my_arx.template get<args::unsigned_long>().value_or(0));
	ASSERT_EQ(42, my_arx.template get<args::floating>().value_or(0));
	ASSERT_EQ(1.8, my_arx.template get<args::double_precision>().value_or(0));
	ASSERT_EQ(my_enum::three, my_arx.template get<args::enumeration>().value_or(my_enum::one));
	const auto string_list = std::vector<std::string_view>{ "abc", "defg" };
	ASSERT_EQ(string_list, my_arx.template get<args::string_list>().value_or(std::vector<std::string_view>{}));
	const auto int_list = std::vector<int>{ 1, 2, 3 };
	ASSERT_EQ(int_list, my_arx.template get<args::integer_list>().value_or(std::vector<int>{}));
	const auto double_list = std::vector<double>{ 2.1, 3.2 };
	ASSERT_EQ(double_list, my_arx.template get<args::double_list>().value_or(std::vector<double>{}));
	ASSERT_EQ("../../", my_arx.template get<args::path>().value_or(""));
	ASSERT_EQ(
		std::chrono::duration_cast<drm::types::timestamp_t>(std::chrono::duration<u_int64_t, std::ratio<60>>(4)),
		my_arx.template get<args::time>().value_or(drm::types::timestamp_t(0))
	);
	const auto positional_list = std::vector<std::string_view>{ "hello", "this", "is", "a", "test", "!" };
	ASSERT_EQ(positional_list, my_arx.get_positionals());
}

TEST(arx, test_bool) {
	static constexpr auto args = std::array{ "scan_combiner", "--bool" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(true, my_arx.template get<args::boolean>().value());
}

TEST(arx, test_integer) {
	static constexpr auto args = std::array{ "scan_combiner", "-i", "42" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(42, my_arx.template get<args::integer>().value_or(0));
}

TEST(arx, test_unsigned_long) {
	static constexpr auto args = std::array{ "scan_combiner", "--unsigned_long", "380" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(380, my_arx.template get<args::unsigned_long>().value_or(0));
}

TEST(arx, test_unsigned_long_negative_value) {
	static constexpr auto args = std::array{ "scan_combiner", "--unsigned_long", "-1" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(0, my_arx.template get<args::unsigned_long>().value_or(0));
}

TEST(arx, test_float) {
	static constexpr auto args = std::array{ "scan_combiner", "-f", "42" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(42, my_arx.template get<args::floating>().value_or(0));
}

TEST(arx, test_double) {
	static constexpr auto args = std::array{ "scan_combiner", "-d", "1.8" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(1.8, my_arx.template get<args::double_precision>().value_or(0));
}

TEST(arx, test_enumeration) {
	static constexpr auto args = std::array{ "scan_combiner", "-e", "three" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(my_enum::three, my_arx.template get<args::enumeration>().value_or(my_enum::one));
}

TEST(arx, test_string_list) {
	static constexpr auto args = std::array{ "scan_combiner", "--string_list", "abc,defg" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	const auto string_list = std::vector<std::string_view>{ "abc", "defg" };
	ASSERT_EQ(string_list, my_arx.template get<args::string_list>().value_or(std::vector<std::string_view>{}));
}

TEST(arx, test_integer_list) {
	static constexpr auto args = std::array{ "scan_combiner", "--integer_list", "1,2,3" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	const auto int_list = std::vector<int>{ 1, 2, 3 };
	ASSERT_EQ(int_list, my_arx.template get<args::integer_list>().value_or(std::vector<int>{}));
}

TEST(arx, test_double_list) {
	static constexpr auto args = std::array{ "scan_combiner", "--double_list", "2.1,3.2" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	const auto double_list = std::vector<double>{ 2.1, 3.2 };
	ASSERT_EQ(double_list, my_arx.template get<args::double_list>().value_or(std::vector<double>{}));
}

TEST(arx, test_path) {
	static constexpr auto args = std::array{ "scan_combiner", "-p", "../../" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ("../../", my_arx.template get<args::path>().value_or(""));
}

TEST(arx, test_time) {
	static constexpr auto args = std::array{ "scan_combiner", "-t", "4min" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	ASSERT_EQ(
		std::chrono::duration_cast<drm::types::timestamp_t>(std::chrono::duration<u_int64_t, std::ratio<60>>(4)),
		my_arx.template get<args::time>().value_or(drm::types::timestamp_t(0))
	);
}

TEST(arx, test_positionals) {
	static constexpr auto args = std::array{ "scan_combiner", "hello", "!" };
	const auto my_arx = arx(
		args.size(),
		args.data(),
		make_arx_flag<args::boolean>('b', "bool"),
		make_arx_flag<args::integer, int>('i', "integer"),
		make_arx_flag<args::unsigned_long, unsigned long>("unsigned_long"),
		make_arx_flag<args::floating, float>('f', "float"),
		make_arx_flag<
			args::double_precision,
			double>('d', "double", arx_parsers::floating_point<double, std::chars_format::hex>),
		make_arx_flag<args::enumeration, my_enum>(
			'e',
			"enum",
			arx_parsers::enumeration<my_enum>{ std::pair{ my_enum::one, "one" },
	                                           std::pair{ my_enum::two, "two" },
	                                           std::pair{ my_enum::three, "three" } }
		),
		make_arx_flag<args::string_list, std::vector<std::string_view>>(
			"string_list",
			arx_parsers::make_list<std::string_view>()
		),
		make_arx_flag<args::integer_list, std::vector<int>>("integer_list", arx_parsers::make_list<int>()),
		make_arx_flag<args::double_list, std::vector<double>>(
			"double_list",
			arx_parsers::make_list<double>(arx_parsers::floating_point<double, std::chars_format::hex>)
		),
		make_arx_flag<args::path, std::filesystem::path>('p', "path"),
		make_arx_flag<args::time, drm::types::timestamp_t>('t', "time")
	);

	const auto positional_list = std::vector<std::string_view>{ "hello", "!" };
	ASSERT_EQ(positional_list, my_arx.get_positionals());
}
