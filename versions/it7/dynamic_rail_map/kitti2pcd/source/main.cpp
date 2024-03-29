#include "converter.hpp"
#include "util/arx.hpp"
#include "util/logger.hpp"

#include <filesystem>
#include <vector>

enum class args {
	recursive,
	help,
	log_level,
	no_colors
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
		make_arx_flag<args::recursive>('r', "recursive"),
		make_arx_flag<args::help>("help"),
		make_arx_flag<args::log_level, logger::level>('l', "log-level", arx_parsers::enumeration<logger::level>{ log_levels }),
		make_arx_flag<args::no_colors>("no-colors")
	);

	if (my_arx.template get<args::help>().value()) {

		auto& logger_cfg = logger::global_config();
		logger_cfg.flags = my_arx.template get<args::no_colors>().value() ? logger::flag::none : logger::flag::colors;
		logger_cfg.threshold = logger::level::generic;

		logger::log("%", "parameter name           description                                           default value");
		logger::info("<positional arguments>   map/chunk directories to be processed");
		logger::info("-r or --recursive        process all chunk folders contained in paths          %%", std::boolalpha, false);
		logger::info("-h or --help             prints parameters with description and default values %%", std::boolalpha, false);
		logger::info("-l or --log-level        log statements below this level will be ignored       %", "log");
		logger::info("--no-colors              disables all logger ANSI colors for printing to files %%", std::boolalpha, false);
		logger::log("");
		logger::log("%", "example commands");
		logger::info("./kitty2pcd % % %", "./chunks/chunk0_0", "./chunks/chunk1_0", "./more_chunks/chunk0_-1");
		logger::info("./kitty2pcd -r %", "./chunks ./more_chunks");

		return EXIT_SUCCESS;
	}

	if (my_arx.template get<args::recursive>().value()) {
		const auto& map_paths = my_arx.get_positionals();

		using std::filesystem::directory_iterator;
		const auto chunk_count = std::accumulate(
			map_paths.begin(),
			map_paths.end(),
			std::size_t{},
			[](const auto count, const auto& map_path) { return count + std::distance(directory_iterator(map_path), directory_iterator{}); }
		);

		if (chunk_count > 1'000) {
			logger::info("Processing % chunks. Grab a coffee this may take a while!", chunk_count);
		} else {
			logger::info("Processing % chunks.", chunk_count);
		}

		auto chunk_index = std::size_t{};
		for (const auto map_path : map_paths) {
			kitti2pcd::convert_chunks(directory_iterator(map_path), directory_iterator{}, chunk_index, chunk_count);
		}
	} else {
		const auto& chunk_paths = my_arx.get_positionals();
		const auto chunk_count = chunk_paths.size();

		logger::info("Processing % chunks.", chunk_count);

		auto chunk_index = std::size_t{};
		kitti2pcd::convert_chunks(chunk_paths.begin(), chunk_paths.end(), chunk_index, chunk_count);
	}

	logger::info("Done!");

	return EXIT_SUCCESS;
}
