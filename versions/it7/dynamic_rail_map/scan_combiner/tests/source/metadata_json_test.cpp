#include "components/metadata.hpp"
#include "modules/metadata_transcoders/json.hpp"

#include "gtest/gtest.h"
#include <fstream>

const std::filesystem::path file_source = "../../../test_resources/metadata";

const drm::metadata::metadata_t metadata01 = {
	{ { "0.3.0",
	    { "/sensors/lidar/velodyne/velodyne_points",
	      drm::types::timestamp_t(1),
	      drm::types::timestamp_t(4'294'967'295'999'999'999),
	      1.0,
	      1.0,
	      30.0,
	      20.0 } } },
	{ { "filtered_rosbag.bag", drm::types::timestamp_milli_t(0), drm::types::timestamp_milli_t(600'493) } },
	{ { 0, 0, drm::types::timestamp_milli_t(1'710'457'075'398), { 0, 7 }, 115'877 } }
};

const drm::metadata::metadata_t metadata02 = {
	{ { "0.3.0",
	    { "/sensors/lidar/velodyne/velodyne_points",
	      drm::types::timestamp_t(1),
	      drm::types::timestamp_t(4'294'967'295'999'999'999),
	      1.0,
	      1.0,
	      30.0,
	      20.0 } } },
	{ { "filtered_rosbag.bag", drm::types::timestamp_milli_t(0), drm::types::timestamp_milli_t(600'493) } },
	{ { 0, 0, drm::types::timestamp_milli_t(1'710'457'075'395), { 0, 29 }, 489'670 } }
};

const drm::metadata::metadata_t metadata03 = {
	{ { "0.3.0",
	    { "/sensors/lidar/velodyne/velodyne_points",
	      drm::types::timestamp_t(1),
	      drm::types::timestamp_t(4'294'967'295'999'999'999),
	      1.0,
	      1.0,
	      30.0,
	      20.0 } } },
	{ { "filtered_rosbag.bag", drm::types::timestamp_milli_t(0), drm::types::timestamp_milli_t(600'493) } },
	{ { 0, 0, drm::types::timestamp_milli_t(1'710'457'075'396), { 0, 44 }, 399'276 } }
};

const drm::metadata::metadata_t metadata04 = {
	{ { "0.3.0",
	    { "/sensors/lidar/velodyne/velodyne_points",
	      drm::types::timestamp_t(1),
	      drm::types::timestamp_t(4'294'967'295'999'999'999),
	      1.0,
	      1.0,
	      30.0,
	      20.0 } } },
	{ { "filtered_rosbag.bag", drm::types::timestamp_milli_t(0), drm::types::timestamp_milli_t(140'625'529'211'744) } },
	{ { 0, 0, drm::types::timestamp_milli_t(1'710'457'081'326), { 0, 12 }, 387'280 } }
};

void test_write(
	const drm::metadata::metadata_t& expected_metadata,
	const std::filesystem::path& tmp_dir,
	const std::filesystem::path& meta_dir
) {
	std::error_code error_code;

	// Writing Metadata
	error_code = drm::metadata_transcoders::json::write(tmp_dir, expected_metadata);
	ASSERT_EQ(error_code.value(), 0);

	std::ifstream example_stream, written_stream;
	std::vector<std::string> example, written;
	example_stream.open(meta_dir);
	written_stream.open(tmp_dir);

	// Reading Files
	std::string tmp;
	while (std::getline(example_stream, tmp)) {
		example.emplace_back(tmp);
	}
	while (std::getline(written_stream, tmp)) {
		written.emplace_back(tmp);
	}

	// Comparing Files
	ASSERT_EQ(example.size(), written.size());
	for (std::size_t i = 0; i < example.size(); ++i) {
		ASSERT_EQ(example.at(i), written.at(i));
	}
}

void test_read(const drm::metadata::metadata_t& expected_metadata, const std::filesystem::path& meta_dir) {
	std::error_code error_code;

	// Testing reading
	drm::metadata::metadata_t read_metadata{};
	error_code = drm::metadata_transcoders::json::read(meta_dir, read_metadata);
	ASSERT_EQ(error_code.value(), 0);
	ASSERT_EQ(read_metadata, expected_metadata);
}

void test_read_error(const std::filesystem::path& meta_dir, const std::error_code expected_error_code) {
	std::error_code error_code;

	// Testing reading
	drm::metadata::metadata_t example_metadata{};
	error_code = drm::metadata_transcoders::json::read(meta_dir, example_metadata);
	ASSERT_EQ(error_code.value(), expected_error_code.value());
}

TEST(metadata_json, general_write) {
	const auto tmp_dir = file_source / "tmp";

	std::error_code fs_error;
	std::filesystem::create_directory(tmp_dir, fs_error);
	ASSERT_EQ(fs_error.value(), 0);

	test_write(metadata01, tmp_dir, file_source / "test01");
	test_write(metadata02, tmp_dir, file_source / "test02");
	test_write(metadata03, tmp_dir, file_source / "test03");
	test_write(metadata04, tmp_dir, file_source / "test04");

	std::filesystem::remove_all(tmp_dir, fs_error);
	ASSERT_EQ(fs_error.value(), 0);
}

TEST(metadata_json, general_read) {
	const auto tmp_dir = file_source / "tmp";

	std::error_code fs_error;
	std::filesystem::create_directory(tmp_dir, fs_error);
	ASSERT_EQ(fs_error.value(), 0);

	test_read(metadata01, file_source / "test01");
	test_read(metadata02, file_source / "test02");
	test_read(metadata03, file_source / "test03");
	test_read(metadata04, file_source / "test04");

	ASSERT_EQ(fs_error.value(), 0);
}

TEST(metadata_json, error_code_test) {

	// Change parameters -> bahnmeter
	test_read_error(file_source / "test05", drm::metadata_transcoders::json_error::codes::member_does_not_exist_json);
	// Chance rosbag/name: "filtered_rosbag.bag" -> 9001
	test_read_error(file_source / "test06", drm::metadata_transcoders::json_error::codes::wrong_type_json);
}
