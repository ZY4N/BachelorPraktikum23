#include "components/metadata.hpp"
#include "components/scan_combiner_pipeline.hpp"
#include "components/unbagger.hpp"
#include "config/default_parameters.hpp"
#include "config/version.hpp"
#include "util/arx.hpp"
#include "util/logger.hpp"

#include <fstream>
#include <string_view>
#include <thread>

enum class args {
	help,
	log_level,
	no_colors,
	threads,

	output_path,

	lidar_topic,
	lidar_sensor_type,

	frame_format,
	metadata_format,

	time_per_block,
	spline_time_padding,

	chunk_size,
	max_radial_distance,
	max_peripheral_distance,
	max_scan_position_deviation,
	origin_ignore_radius,

	relative_begin_time,
	relative_end_time
};

int main(int num_args, char* args[]) {

	//-------------[ argument parsing ]-------------//
	using namespace std::string_view_literals;

	static constexpr auto log_levels = std::array{
		std::pair{ logger::level::mute, "mute"sv }, std::pair{ logger::level::error, "error"sv },
		std::pair{ logger::level::warn, "warn"sv }, std::pair{ logger::level::info, "info"sv },
		std::pair{ logger::level::log, "log"sv },   std::pair{ logger::level::debug, "debug"sv }
	};

	const auto my_arx = arx(
		num_args,
		args,
		make_arx_flag<args::help>('h', "help"),
		make_arx_flag<args::log_level, logger::level>(
			'l',
			"log-level",
			arx_parsers::enumeration<logger::level>{ log_levels }
		),
		make_arx_flag<args::no_colors>("no-colors"),
		make_arx_flag<args::threads, unsigned>("threads"),
		make_arx_flag<args::output_path, std::filesystem::path>('o', "output"),
		make_arx_flag<args::lidar_topic, std::string_view>("lidar-topic"),
		make_arx_flag<args::lidar_sensor_type, drm::point_cloud_parsing::sensor_type>(
			"lidar-sensor-type",
			arx_parsers::enumeration<drm::point_cloud_parsing::sensor_type>{
				drm::point_cloud_parsing::get_sensor_name_lookup() }
		),
		make_arx_flag<args::frame_format, drm::frame_exportation::frame_format>(
			"frame-format",
			arx_parsers::enumeration<drm::frame_exportation::frame_format>{
				drm::frame_exportation::get_format_name_lookup() }
		),
		make_arx_flag<args::metadata_format, drm::metadata_transcoding::metadata_format>(
			"metadata-format",
			arx_parsers::enumeration<drm::metadata_transcoding::metadata_format>{
				drm::metadata_transcoding::get_format_name_lookup() }
		),
		make_arx_flag<args::time_per_block, drm::types::timestamp_t>("time-per-block"),
		make_arx_flag<args::spline_time_padding, drm::types::timestamp_t>("spline-time-padding"),
		make_arx_flag<args::chunk_size, double>("chunk-size"),
		make_arx_flag<args::max_radial_distance, double>("max-radial-dist"),
		make_arx_flag<args::max_peripheral_distance, double>("max-peripheral-dist"),
		make_arx_flag<args::max_scan_position_deviation, double>("max-scan-pos-deviation"),
		make_arx_flag<args::origin_ignore_radius, double>("origin-ignore-radius"),
		make_arx_flag<args::relative_begin_time, drm::types::timestamp_t>("relative-begin-time"),
		make_arx_flag<args::relative_end_time, drm::types::timestamp_t>("relative-end-time")
	);

	namespace dfp = drm::default_parameters;

	if (my_arx.template get<args::help>().value()) {

		auto& logger_cfg = logger::global_config();
		logger_cfg.flags = my_arx.template get<args::no_colors>().value() ? logger::flag::none : logger::flag::colors;
		logger_cfg.threshold = logger::level::generic;

		const auto print_other_options = [](const auto& options, const auto& selected) {
			auto out = std::stringstream{};
			for (const auto& [type, name] : options) {
				if (type != selected) {
					out << ", " << name;
				}
			}
			return out.str();
		};

		logger::log(
			"%",
			"parameter name           description                                               default value"
		);
		logger::info("<positional arguments>   rosbag input paths");
		logger::info("-o or --output           chunk folder output path");
		logger::info("-h or --help             prints parameters with description and default values");
		logger::info(
			"-l or --log-level        log statements below this level will be ignored           [%]%",
			dfp::log_level,
			print_other_options(log_levels, dfp::log_level)
		);
		logger::info(
			"--no-colors              disables all logger ANSI colors for printing to files     %%",
			std::boolalpha,
			false
		);
		logger::info(
			"--frame-format           output format for chunk and point data                    [%]%",
			dfp::frame_format,
			print_other_options(drm::frame_exportation::get_format_name_lookup(), dfp::frame_format)
		);
		logger::info(
			"--metadata-format        output format for chunk metadata                          [%]%",
			dfp::metadata_format,
			print_other_options(drm::metadata_transcoding::get_format_name_lookup(), dfp::metadata_format)
		);
		logger::info(
			"--threads                number of utilized concurrent threads                     %",
			dfp::num_threads
		);
		logger::info(
			"--lidar-topic            the rosbag topic for the point cloud data                 %",
			dfp::lidar_topic
		);
		logger::info(
			"--lidar-sensor-type      sensor that produced the point cloud data                 [%]%",
			dfp::lidar_sensor_type,
			print_other_options(drm::point_cloud_parsing::get_sensor_name_lookup(), dfp::lidar_sensor_type)
		);
		logger::info(
			"--time-per-block         time limit for data to be processed in one block          %min",
			dfp::time_per_block.count()
		);
		logger::info(
			"--spline-time-padding    time loaded before and after block to build splines       %s",
			dfp::spline_time_padding.count()
		);
		logger::info(
			"--chunk-size             chunk grid size in meters                                 %m",
			dfp::chunk_size
		);
		logger::info(
			"--max-radial-dist        maximum radial distance from sensor in meters             %m",
			dfp::max_radial_distance
		);
		logger::info(
			"--max-peripheral-dist    maximum peripheral distance from sensor in meters         %m",
			dfp::max_peripheral_distance
		);
		logger::info(
			"--max-scan-pos-deviation maximum frame scan position deviation in meters           %m",
			dfp::max_scan_position_deviation
		);
		logger::info(
			"--origin-ignore-radius   radius for transform ignore zone around origin in meters  %m",
			dfp::origin_ignore_radius
		);
		logger::info(
			"--relative-begin-time    time offset from rosbag begin time                        %ns",
			dfp::relative_begin_time.count()
		);
		logger::info(
			"--relative-end-time      time limit from rosbag begin time                         %ns",
			dfp::relative_end_time.count()
		);
		logger::log("");
		logger::log("%", "example command");
		logger::info(
			"./drm_input_node my_rosbag.bag -o % --time-per-block % --max-scan-pos-deviation % -l %",
			"./chunks",
			"8min",
			"1.0",
			"debug"
		);
		return EXIT_SUCCESS;
	}

	//-------------[ logger setup ]-------------//

	auto& logger_cfg = logger::global_config();
	logger_cfg.threshold = my_arx.template get<args::log_level>().value_or(dfp::log_level);

	switch (logger_cfg.threshold) {
	case logger::level::mute:
	case logger::level::error:
	case logger::level::warn:
		logger_cfg.flags = logger::minimal_flags();
		break;
	case logger::level::info:
	case logger::level::log:
		logger_cfg.flags = logger::default_flags();
		break;
	case logger::level::debug:
	case logger::level::generic:
		logger_cfg.flags = logger::debug_flags() & ~logger::flag::function_name;
		break;
	}

	if (my_arx.template get<args::no_colors>().value()) {
		logger_cfg.flags &= ~logger::flag::colors;
	}

	//-------------[ initialization ]-------------//

	using namespace std::chrono_literals;

	// First parse mandatory parameters.

	const auto& raw_input_paths = my_arx.get_positionals();
	if (raw_input_paths.empty()) {
		logger::error("No rosbag paths provided.");
		return EXIT_FAILURE;
	}

	auto output_path_opt = my_arx.template get<args::output_path>();
	if (not output_path_opt.has_value()) {
		logger::error("No output path provided.");
		return EXIT_FAILURE;
	}
	const auto output_path = std::move(output_path_opt).value();

	// Then parse optional parameters with default values.
	const auto num_threads = my_arx.template get<args::threads>().value_or(dfp::num_threads);
	const auto lidar_topic = my_arx.template get<args::lidar_topic>().value_or(dfp::lidar_topic);
	const auto lidar_sensor_type = my_arx.template get<args::lidar_sensor_type>().value_or(dfp::lidar_sensor_type);
	const auto frame_format = my_arx.template get<args::frame_format>().value_or(dfp::frame_format);
	const auto metadata_format = my_arx.template get<args::metadata_format>().value_or(dfp::metadata_format);
	const auto time_per_block = my_arx.template get<args::time_per_block>().value_or(dfp::time_per_block);
	const auto spline_time_padding = my_arx.template get<args::spline_time_padding>().value_or(dfp::spline_time_padding
	);
	const auto chunk_size = my_arx.template get<args::chunk_size>().value_or(dfp::chunk_size);
	const auto max_radial_distance = my_arx.template get<args::max_radial_distance>().value_or(dfp::max_radial_distance
	);
	const auto max_peripheral_distance = my_arx.template get<args::max_peripheral_distance>().value_or(
		dfp::max_peripheral_distance
	);
	const auto max_scan_position_deviation = my_arx.template get<args::max_scan_position_deviation>().value_or(
		dfp::max_scan_position_deviation
	);
	const auto origin_ignore_radius = my_arx.template get<args::origin_ignore_radius>().value_or(
		dfp::origin_ignore_radius
	);
	const auto relative_begin_time = my_arx.template get<args::relative_begin_time>().value_or(dfp::relative_begin_time
	);
	const auto relative_end_time = my_arx.template get<args::relative_end_time>().value_or(dfp::relative_end_time);

	//-------------[ setup pipeline ]-------------//

	logger::info("Running Scan Combiner v%.%.%", drm::version::major, drm::version::minor, drm::version::revision);

	const auto thread_portion = [&num_threads](const double portion) {
		return std::max(
			std::size_t{ 1 },
			static_cast<std::size_t>(std::round(portion * static_cast<double>(num_threads)))
		);
	};

	const auto num_point_extraction_threads = thread_portion(dfp::point_extraction_thread_portion);
	const auto num_transform_extraction_threads = thread_portion(dfp::transform_extraction_thread_portion);
	const auto num_velocity_extraction_threads = thread_portion(dfp::velocity_extraction_thread_portion);
	const auto metadata_io_threads = thread_portion(dfp::metadata_io_thread_portion);
	const auto processing_thread_multiplier = dfp::processing_thread_multiplier;

	auto pipeline = drm::scan_combiner_pipeline{ processing_thread_multiplier,
		                                         num_point_extraction_threads,
		                                         num_transform_extraction_threads,
		                                         num_velocity_extraction_threads,
		                                         metadata_io_threads,
		                                         std::string(lidar_topic),
		                                         lidar_sensor_type,
		                                         frame_format,
		                                         metadata_format,
		                                         relative_begin_time,
		                                         relative_end_time,
		                                         time_per_block,
		                                         spline_time_padding,
		                                         chunk_size,
		                                         origin_ignore_radius,
		                                         max_scan_position_deviation,
		                                         max_radial_distance,
		                                         max_peripheral_distance };

	//-------------[ preparing input paths ]-------------//

	std::vector<std::filesystem::path> input_paths;
	input_paths.reserve(raw_input_paths.size());

	for (const auto& raw_input_path : raw_input_paths) {
		try {
			input_paths.emplace_back(raw_input_path);
		} catch (const std::exception& e) {
			logger::warn("Skipping path '%' because error occured while parsing: %.", raw_input_path, e.what());
			continue;
		}
	}

	//-------------[ processing the rosbags ]-------------//

	const auto error = pipeline.process_rosbags(input_paths, output_path);

	if (error) {
		logger::error("Error processing rosbags: %", error);
		return EXIT_FAILURE;
	}

	logger::info("All data processed!");

	return EXIT_SUCCESS;
}
