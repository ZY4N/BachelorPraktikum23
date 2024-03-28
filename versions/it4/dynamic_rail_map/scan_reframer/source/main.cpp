#include "modules/lord_tachuncker.hpp"
#include "modules/metadata.hpp"
#include "modules/unbagger.hpp"
#include "util/arx.hpp"
#include "util/logger.hpp"
#include "version.hpp"

#include <fstream>
#include <thread>

enum class args {
	path_output,
	lidar_topics,
	begin_time,
	end_time,
	max_radial_distance,
	max_peripheral_distance,

	time_per_block,
	max_scan_position_deviation,
	max_position_deviation,
	threads,
	logger,
	help
};

int main(int num_args, char* args[]) {

	//-------------[ argument parsing ]-------------//

	const auto my_arx = arx(
		num_args,
		args,
		make_arx_flag<args::path_output, std::filesystem::path>('o', "output"),
		make_arx_flag<args::lidar_topics, std::vector<std::string>>(
			't',
			"topics",
			arx_parsers::make_list<std::string>()
		),
		make_arx_flag<args::begin_time, drm::types::timestamp_t>("relative-begin"),
		make_arx_flag<args::end_time, drm::types::timestamp_t>("relative-end"),
		make_arx_flag<args::max_radial_distance, unsigned int>("max-radial-dist"),
		make_arx_flag<args::max_peripheral_distance, unsigned int>("max-peripheral-dist"),
		make_arx_flag<args::time_per_block, drm::types::timestamp_t>("time-per-block"),
		make_arx_flag<args::max_scan_position_deviation, double>("max-scan-pos-deviation"),
		make_arx_flag<args::max_position_deviation, double>("max-position-deviation"),
		make_arx_flag<args::threads, unsigned long>("threads"),
		make_arx_flag<args::logger, logger::level>(
			'l',
			"logger-level",
			arx_parsers::enumeration<logger::level>{
				std::pair{ logger::level::mute, "mute" },
				std::pair{ logger::level::error, "error" },
				std::pair{ logger::level::warn, "warn" },
				std::pair{ logger::level::info, "info" },
				std::pair{ logger::level::log, "log" },
				std::pair{ logger::level::debug, "debug" },
				std::pair{ logger::level::generic, "generic" },
			}
		),
		make_arx_flag<args::help>("help")
	);

	if (my_arx.template get<args::help>().value()) {
		std::cout
			<< "Input-Paths              set without specific flag\n"
			   "-o or --output           sets the output-path\n"
			   "-t or --topics           sets the topic-path, per Default \"/sensors/lidar/velodyne/velodyne_points\"\n"
			   "--relative-begin         sets begin time inside the Lider-Scans, per default ros::TIME_MIN\n"
			   "--relative-end           sets end time inside the Lider-Scans, per default ros::TIME_MAX\n"
			   "--max-radial-dist        sets max. radial distance in meters, per default 50m\n"
			   "--max-peripheral-dist    sets max. peripheral distance in meters, per default 20m\n"
			   "--time-per-block         sets max time that is in progress at a time, per default 10min\n"
			   "--max-scan-pos-deviation sets max. distance between scan positions, per default 1m\n"
			   "--threads                sets number of used threads, per default 1\n"
			   "-l or --logger-level     sets level of logger, possible levels: mute, error, warn, info, log, debug "
			   "and generic, per default log"
			   "--max-position-deviation  set the maximum allowed position deviation between transform in meters, per "
			   "default 100m. ";
		return 0;
	}

	//-------------[ logger setup ]-------------//

	auto& logger_ctx = logger::global_context();
	logger_ctx.m_level = my_arx.template get<args::logger>().value_or(logger::level::log);
	switch (logger_ctx.m_level) {
	case logger::level::mute:
	case logger::level::error:
	case logger::level::warn:
		logger_ctx.m_flags = logger::minimal_flags();
		break;
	case logger::level::info:
	case logger::level::log:
		logger_ctx.m_flags = logger::default_flags();
		break;
	case logger::level::debug:
	case logger::level::generic:
		logger_ctx.m_flags = logger::debug_flags();
		break;
	}

	//-------------[ initialization ]-------------//

	const auto lidar_topics_vector = my_arx.template get<args::lidar_topics>().value_or(std::vector<std::string>{
		"/sensors/lidar/velodyne/velodyne_points" });

	logger::info("Extracting frames from %", lidar_topics_vector.front());

	const std::size_t num_threads = my_arx.template get<args::threads>().value_or(48);
	using namespace std::chrono_literals;
	const auto relative_begin_time = my_arx.template get<args::begin_time>().value_or(
		drm::ros_time_to_timestamp_t(ros::TIME_MIN)
	);
	const auto relative_end_time = my_arx.template get<args::end_time>().value_or(
		drm::ros_time_to_timestamp_t(ros::TIME_MAX)
	);
	const auto time_per_block = my_arx.template get<args::time_per_block>().value_or(1h);

	const auto transform_padding = 10s;

	const auto max_position_deviation = my_arx.template get<args::max_position_deviation>().value_or(100.0);

	const auto max_scan_position_deviation = my_arx.template get<args::max_scan_position_deviation>().value_or(1.0);
	logger::info("Maximum scan position deviation % m", max_scan_position_deviation);

	// const auto filter = drm::distance_filtering::create_simple_filter(50);

	const auto max_radial_distance = my_arx.template get<args::max_radial_distance>().value_or(30);
	const auto max_peripheral_distance = my_arx.template get<args::max_peripheral_distance>().value_or(20);

	// using filter_t = std::remove_reference_t<std::remove_cv_t<decltype(filter)>>;

	const auto& input_paths = my_arx.get_positionals();

	const auto output_path_opt = my_arx.template get<args::path_output>();
	if (not output_path_opt.has_value()) {
		logger::error("No output path provided.");
		exit(1);
	}

	const auto reframer_config = drm::metadata::reframer_config_t{ drm::metadata::get_version(),
		                                                           { lidar_topics_vector,
		                                                             relative_begin_time,
		                                                             relative_end_time,
		                                                             max_position_deviation,
		                                                             max_scan_position_deviation,
		                                                             max_radial_distance,
		                                                             max_peripheral_distance } };

	const auto output_path = my_arx.template get<args::path_output>().value();

	std::cout << std::fixed << std::setprecision(4);

	//-------------[ reframer ]-------------//

	auto bag_index = std::size_t{};
	auto frame_offset = std::size_t{};
	auto lord = drm::lord_tachuncker{ lidar_topics_vector,    num_threads,
		                              relative_begin_time,    relative_end_time,
		                              time_per_block,         transform_padding,
		                              max_position_deviation, max_scan_position_deviation,
		                              max_radial_distance,    max_peripheral_distance };

	for (const auto raw_filename : input_paths) {
		++bag_index;

		auto filename = std::filesystem::path{};
		try {
			filename = raw_filename;
		} catch (const std::exception& e) {
			logger::warn("Error while parsing path: %", e.what());
			continue;
		}
		logger::info("Opening rosbag (%/%) from %", bag_index, input_paths.size(), filename);
		if (lord.extract_and_filter(filename, output_path, frame_offset)) {
			logger::warn("Error while extracting from %", filename);
		}
	}
}
