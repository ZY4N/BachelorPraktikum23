#pragma once

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cinttypes>
#include <filesystem>
#include <iostream>
#include <string_view>
#include <thread>
#include <tuple>

namespace logger_internal {

using flags_int_t = std::uint16_t;

}

/**
 * @brief A lightweight logging library providing color-coded output and
 * flexible configuration.
 *
 * @details This namespace serves as a wrapper around std::ostream, offering a
 * simple yet powerful logging interface with support for ANSI color-coded log
 * levels. It provides a global logging context as well as customizable logger
 * contexts, allowing users to configure output streams, log levels and more.
 */
namespace logger {

//--------------[ declarations ]--------------//

/**
 * @brief Placeholder symbol used in format strings to signal value position.
 */
static constexpr char format_symbol = '%';

/**
 * @brief Symbol to escape the placeholder symbol in the format string..
 */
static constexpr char escape_format_symbol = '\\';

static_assert(format_symbol != escape_format_symbol);

/**
 * @brief Enumeration representing the log levels.
 *
 * The log levels are ordered from least verbose to most verbose, as follows:
 * - @c mute:	 Indicates that no log messages should be emitted.
 * - @c error:   Used for critical errors that require immediate attention.
 * - @c warn:	 Used for potential issues that may need attention.
 * - @c info:	 Used for significant events and information about the process.
 * - @c log:	 General log messages providing information about the
 * application's operation.
 * - @c debug:   Detailed debug information helpful for troubleshooting.
 * - @c generic: A catch-all levels for generic log messages.
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

inline std::ostream &operator<<(std::ostream &out, logger::level level) {
  switch (level) {
  case logger::level::mute:
    return out << "mute";
  case logger::level::error:
    return out << "error";
  case logger::level::warn:
    return out << "warn";
  case logger::level::info:
    return out << "info";
  case logger::level::log:
    return out << "log";
  case logger::level::debug:
    return out << "debug";
  case logger::level::generic:
    return out << "generic";
  default:
    return out << "unknown(" << std::to_string(static_cast<int>(level)) << ")";
  }
}

/**
 * @brief Enumeration of feature flag for the logger class.
 *
 * The `flag` enum is a set of feature flag used in the logger class to control
 * the behavior of log message output. Each flag corresponds to a specific
 * feature or information component that can be included in log messages,
 * providing a flexible and customizable way to tailor the levels of detail
 * included in log outputs based on the specific needs of the application.
 *
 * @c none:          Disables all flag. Log messages will only include the
 * message without any additional information.
 * @c all:           Enables all available flag. Log messages will include all
 * following features:
 * @c colors:        Enables color-coding for log messages, providing visual
 * cues for different log levels.
 * @c locking:       Enables the use of a spin lock mechanism for thread-safe
 * log message output.
 * @c identifier
 * -------------------------------------------------------------------------------------+
 * @c thread_id
 * -----------------------------------------------------------------------+ |
 * @c function_name
 * ------------------------------------------------------------+          | |
 * @c line_number    ------------------------------------------------------+ |
 * |             |
 * @c filename       -----------------------------------------------+      | |
 * |             |
 * @c level_name     ----------------------------------------+      |      | |
 * |             |
 * @c timestamp      -------------------------------+        |      |      | |
 * |             |
 * @c time           ----------------+              |        |      |      | |
 * |             |
 * @c date           ----+           |              |        |      |      | |
 * |             | |           |              |        |      |      |     | | |
 *                   [2024-1-8][19:44:9.535][1704739449535][log][
 * main.cpp:61][main][140654793804672][extractor] hello!
 */
enum class flag : logger_internal::flags_int_t {
  none = 0,
  all = std::numeric_limits<logger_internal::flags_int_t>::max(),
  colors = (1 << 0),
  locking = (1 << 1),
  date = (1 << 2),
  time = (1 << 3),
  timestamp = (1 << 4),
  level_name = (1 << 5),
  filename = (1 << 6),
  line_number = (1 << 7),
  function_name = (1 << 8),
  thread_id = (1 << 9)
};

inline flag default_flags();
inline flag log_file_flags();
inline flag debug_flags();
inline flag minimal_flags();

/**
 * @brief Context structure for configuring the behavior of the logger class.
 *
 * The `context` struct provides a means to configure the logger's behavior by
 * specifying the output streams, log message formatting flag, log levels, and
 * an optional spin lock for thread safety.
 *
 * @c out:         Pointer to the output stream for standard log messages.
 * @c err:         Pointer to the output stream for error log messages.
 * @c lock:        Atomic flag used for thread-safe log message output when the
 * `locking` flag is enabled.
 */
struct context {
  std::ostream *out;
  std::ostream *err;
  std::atomic_flag lock = ATOMIC_FLAG_INIT;

  inline context(std::ostream &, std::ostream &);
};

/**
 * @brief Config structure for configuring the behavior of the logger class.
 *
 * The `context` struct provides a means to configure the logger's behavior by
 * specifying the output streams, log message formatting flag, log levels, and
 * an optional spin lock for thread safety.
 *
 * @c flag:       Flags representing the formatting options for log messages.
 * See the flag enum for details.
 * @c threshold:       Log levels setting, controlling the verbosity of logged
 * messages. See the levels enum for details.
 * @c m_identifier:  Atomic flag used for thread-safe log message output when
 * the `locking` flag is enabled.
 */
struct config {
  flag flags;
  level threshold;
  std::string identifier{};
};

namespace logger_internal {

struct source_location {
  std::string_view function, file;
  int line;

  [[nodiscard]] inline static logger_internal::source_location
  current(std::string_view file = __builtin_FILE(), int line = __builtin_LINE(),
          std::string_view function = __builtin_FUNCTION()) {
    return {function, file, line};
  }
};

} // namespace logger_internal

//--------------[ global logger ]--------------//

inline context &global_context();

inline config &global_config();

/**
 * @brief Formats and logs an error message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the
 * format string.
 * @param fmt   The format string for the error message, supporting
 * placeholders.
 * @param args  The values to be formatted and included in the error message.
 *
 * @note Extra placeholders or values are ignored.
 */
template <typename... Args> struct error {
  explicit inline error(std::string_view fmt, Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
  explicit inline error(context &ctx, std::string_view fmt, Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
  explicit inline error(const config &cfg, std::string_view fmt, Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
  explicit inline error(context &ctx, const config &cfg, std::string_view fmt,
                        Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
};

template <typename... Args>
error(std::string_view fmt, Args &&...) -> error<Args...>;

template <typename... Args>
error(context &ctx, std::string_view fmt, Args &&...) -> error<Args...>;

template <typename... Args>
error(const config &cfg, std::string_view fmt, Args &&...) -> error<Args...>;

template <typename... Args>
error(context &ctx, const config &cfg, std::string_view fmt, Args &&...)
    -> error<Args...>;

/**
 * @brief Formats and logs a warning message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the
 * format string.
 * @param fmt   The format string for the warn message, supporting placeholders.
 * @param args  The values to be formatted and included in the warn message.
 *
 * @note Extra placeholders or values are ignored.
 */
template <typename... Args> struct warn {
  explicit inline warn(std::string_view fmt, Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
  explicit inline warn(context &ctx, std::string_view fmt, Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
  explicit inline warn(const config &cfg, std::string_view fmt, Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
  explicit inline warn(context &ctx, const config &cfg, std::string_view fmt,
                       Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
};

template <typename... Args>
warn(std::string_view fmt, Args &&...) -> warn<Args...>;

template <typename... Args>
warn(context &ctx, std::string_view fmt, Args &&...) -> warn<Args...>;

template <typename... Args>
warn(const config &cfg, std::string_view fmt, Args &&...) -> warn<Args...>;

template <typename... Args>
warn(context &ctx, const config &cfg, std::string_view fmt, Args &&...)
    -> warn<Args...>;

/**
 * @brief Formats and logs an info message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the
 * format string.
 * @param fmt   The format string for the info message, supporting placeholders.
 * @param args  The values to be formatted and included in the info message.
 *
 * @note Extra placeholders or values are ignored.
 */
template <typename... Args> struct info {
  explicit inline info(std::string_view fmt, Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
  explicit inline info(context &ctx, std::string_view fmt, Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
  explicit inline info(const config &cfg, std::string_view fmt, Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
  explicit inline info(context &ctx, const config &cfg, std::string_view fmt,
                       Args &&...args,
                       const logger_internal::source_location &location =
                           logger_internal::source_location::current());
};

template <typename... Args>
info(std::string_view fmt, Args &&...) -> info<Args...>;

template <typename... Args>
info(context &ctx, std::string_view fmt, Args &&...) -> info<Args...>;

template <typename... Args>
info(const config &cfg, std::string_view fmt, Args &&...) -> info<Args...>;

template <typename... Args>
info(context &ctx, const config &cfg, std::string_view fmt, Args &&...)
    -> info<Args...>;

/**
 * @brief Formats and logs an info message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the
 * format string.
 * @param fmt   The format string for the info message, supporting placeholders.
 * @param args  The values to be formatted and included in the info message.
 *
 * @note Extra placeholders or values are ignored.
 */
template <typename... Args> struct log {
  explicit inline log(std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location =
                          logger_internal::source_location::current());
  explicit inline log(context &ctx, std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location =
                          logger_internal::source_location::current());
  explicit inline log(const config &cfg, std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location =
                          logger_internal::source_location::current());
  explicit inline log(context &ctx, const config &cfg, std::string_view fmt,
                      Args &&...args,
                      const logger_internal::source_location &location =
                          logger_internal::source_location::current());
};

template <typename... Args>
log(std::string_view fmt, Args &&...) -> log<Args...>;

template <typename... Args>
log(context &ctx, std::string_view fmt, Args &&...) -> log<Args...>;

template <typename... Args>
log(const config &cfg, std::string_view fmt, Args &&...) -> log<Args...>;

template <typename... Args>
log(context &ctx, const config &cfg, std::string_view fmt, Args &&...)
    -> log<Args...>;

/**
 * @brief Formats and logs a debug message using the @c global_instance.
 *
 * The format string may contain placeholders (@c fmt_symbol)
 * replaced by corresponding values provided in the arguments (@c args).
 *
 * @tparam Args Variadic template for the types of arguments passed to the
 * format string.
 * @param fmt   The format string for the debug message, supporting
 * placeholders.
 * @param args  The values to be formatted and included in the debug message.
 *
 * @note Extra placeholders or values are ignored.
 */
template <typename... Args> struct debug {
  explicit inline debug(std::string_view fmt, Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
  explicit inline debug(context &ctx, std::string_view fmt, Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
  explicit inline debug(const config &cfg, std::string_view fmt, Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
  explicit inline debug(context &ctx, const config &cfg, std::string_view fmt,
                        Args &&...args,
                        const logger_internal::source_location &location =
                            logger_internal::source_location::current());
};

template <typename... Args>
debug(std::string_view fmt, Args &&...) -> debug<Args...>;

template <typename... Args>
debug(context &ctx, std::string_view fmt, Args &&...) -> debug<Args...>;

template <typename... Args>
debug(const config &cfg, std::string_view fmt, Args &&...) -> debug<Args...>;

template <typename... Args>
debug(context &ctx, const config &cfg, std::string_view fmt, Args &&...)
    -> debug<Args...>;

/**
 * @brief  Formats and logs a message to the given @c std::ostream.
 *
 * Handles the formatting of a log message based on the provided log levels,
 * evaluates whether it meets the specified threshold levels, and writes the
 * formatted message to the given @c std::ostream.
 *
 * @tparam Args	 Variadic template for the types of arguments passed to the
 * format string.
 * @param out	   The @c std::ostream to which the formatted message will be
 * written.
 * @param log_level The log @c levels of the message being logged.
 * @param threshold Messages below this levels will be ignored.
 * @param format	The format string for the message, supporting
 * placeholders.
 * @param args	  The values to be formatted and included in the message.
 */
template <typename... Args>
inline void println(const logger_internal::source_location &location,
                    context &ctx, const config &cfg, logger::level log_level,
                    const std::string_view &format, Args &&...args);

/**
 * @brief  Formats and logs a message to the given @c std::ostream.
 *
 * Handles the formatting of a log message based on the provided log levels,
 * evaluates whether it meets the specified threshold levels, and writes the
 * formatted message to the given @c std::ostream.
 *
 * @tparam Args	 Variadic template for the types of arguments passed to the
 * format string.
 * @param out	   The @c std::ostream to which the formatted message will be
 * written.
 * @param log_level The log @c levels of the message being logged.
 * @param threshold Messages below this levels will be ignored.
 * @param format	The format string for the message, supporting
 * placeholders.
 * @param args	  The values to be formatted and included in the message.
 */
template <typename... Args>
inline void println(const logger_internal::source_location &location,
                    logger::level log_level, const std::string_view &format,
                    Args &&...args);

} // namespace logger

//--------------[ logger_internal implementation ]--------------//

namespace logger_internal {

enum class color : std::uint8_t {
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

inline constexpr std::size_t num_digits(std::uint32_t n,
                                        std::uint32_t base = 10) {
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

template <std::uint32_t N, std::uint32_t B = 10>
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

template <color color, bool bright> inline constexpr auto create_ansi_color() {

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

  constexpr auto color_str_length =
      (prefix.size() + color_index_str.size() + postfix.size());
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

inline constexpr auto reset_color_array =
    create_ansi_color<color::reset, false>();
inline constexpr auto reset_color =
    std::string_view(reset_color_array.data(), reset_color_array.size());

inline constexpr auto internal_color_array =
    create_ansi_color<color::magenta, true>();
inline constexpr auto internal_color =
    std::string_view(internal_color_array.data(), internal_color_array.size());

inline constexpr std::size_t num_levels = 6;
inline constexpr std::array<std::string_view, num_levels> level_names{
    "error", "warning", "info", "log", "debug", "generic"};

template <bool bright, color... colors>
inline constexpr auto create_color_tuple() {
  return std::make_tuple(create_ansi_color<colors, bright>()...);
}

template <typename... Ts, std::size_t... Is>
inline constexpr auto build_string_lookup(const std::tuple<Ts...> &string_tuple,
                                          std::index_sequence<Is...>) {
  return std::array{std::string_view(std::get<Is>(string_tuple).data(),
                                     std::get<Is>(string_tuple).size())...};
}

inline constexpr auto level_dark_color_tuple =
    create_color_tuple<false, color::red, color::yellow, color::green,
                       color::white, color::blue, color::white>();

inline constexpr auto level_dark_color_lookup = build_string_lookup(
    level_dark_color_tuple, std::make_index_sequence<num_levels>{});

inline constexpr auto level_bright_color_tuple =
    create_color_tuple<true, color::red, color::yellow, color::green,
                       color::white, color::blue, color::white>();

inline constexpr auto level_bright_color_lookup = build_string_lookup(
    level_bright_color_tuple, std::make_index_sequence<num_levels>{});

inline void print_format(std::ostream &out, const std::string_view &,
                         const std::string_view &reset_clr,
                         const std::string_view &internal_clr,
                         std::string_view format) {
  std::size_t next_index;
  while ((next_index = format.find(logger::format_symbol)) !=
         std::string::npos) {
    if (next_index != 0 and
        format[next_index - 1] == logger::escape_format_symbol) {
      out.write(format.data(), static_cast<std::streamsize>(next_index - 1));
      out.put(logger::format_symbol);
    } else {
      out.write(format.data(), static_cast<std::streamsize>(next_index));
      out << internal_clr << "<LOGGER:MISSING_VALUE>" << reset_clr;
    }
    format = format.substr(next_index + sizeof(logger::format_symbol));
  }
  out << format;
}

template <typename First, typename... Rest>
inline void print_format(std::ostream &out, const std::string_view &value_clr,
                         const std::string_view &reset_clr,
                         const std::string_view &internal_clr,
                         std::string_view format, First &&first,
                         Rest &&...rest) {
  std::size_t next_index;
  while ((next_index = format.find(logger::format_symbol)),
         next_index != std::string::npos and next_index != 0 and
             format[next_index - 1] == logger::escape_format_symbol) {
    out.write(format.data(), static_cast<std::streamsize>(next_index - 1));
    out.put(logger::format_symbol);
    format = format.substr(next_index + sizeof(logger::format_symbol));
  }
  if (next_index == std::string::npos) {
    out << format << ' ' << internal_clr
        << "<LOGGER:MISSING_PLACEHOLDER(S)_FOR: ";
    out << value_clr << std::forward<First>(first) << internal_clr;
    ((out << ", " << value_clr << std::forward<Rest>(rest) << internal_clr),
     ...);
    out << ">" << reset_clr;
  } else {
    out.write(format.data(), static_cast<std::streamsize>(next_index));
    out << value_clr << std::forward<First>(first) << reset_clr;
    print_format(out, value_clr, reset_clr, internal_clr,
                 format.substr(next_index + sizeof(logger::format_symbol)),
                 std::forward<Rest>(rest)...);
  }
}
} // namespace logger_internal

[[nodiscard]] inline constexpr logger::flag operator|(const logger::flag &a,
                                                      const logger::flag &b) {
  return static_cast<logger::flag>(
      static_cast<logger_internal::flags_int_t>(a) |
      static_cast<logger_internal::flags_int_t>(b));
}

[[nodiscard]] inline constexpr logger::flag operator&(const logger::flag &a,
                                                      const logger::flag &b) {
  return static_cast<logger::flag>(
      static_cast<logger_internal::flags_int_t>(a) &
      static_cast<logger_internal::flags_int_t>(b));
}

[[nodiscard]] inline constexpr logger::flag operator^(const logger::flag &a,
                                                      const logger::flag &b) {
  return static_cast<logger::flag>(
      static_cast<logger_internal::flags_int_t>(a) ^
      static_cast<logger_internal::flags_int_t>(b));
}

[[nodiscard]] inline constexpr logger::flag operator~(const logger::flag &a) {
  return static_cast<logger::flag>(
      ~static_cast<logger_internal::flags_int_t>(a));
}

inline constexpr logger::flag &operator|=(logger::flag &a,
                                          const logger::flag &b) {
  return a = a | b;
}

inline constexpr logger::flag &operator&=(logger::flag &a,
                                          const logger::flag &b) {
  return a = a & b;
}

inline constexpr logger::flag &operator^=(logger::flag &a,
                                          const logger::flag &b) {
  return a = a ^ b;
}

logger::context::context(std::ostream &new_out, std::ostream &new_err)
    : out{&new_out}, err{&new_err} {}

namespace logger {

logger::flag default_flags() {
  return (flag::colors | flag::locking | flag::time | flag::level_name |
          flag::function_name);
}

logger::flag log_file_flags() {
  return (flag::locking | flag::timestamp | flag::level_name |
          flag::function_name);
}

logger::flag debug_flags() {
  return (flag::colors | flag::locking | flag::time | flag::level_name |
          flag::filename | flag::line_number | flag::function_name |
          flag::thread_id);
}

logger::flag minimal_flags() { return (flag::colors | flag::locking); }

context &global_context() {
  static auto ctx = context(std::cout, std::cerr);
  return ctx;
}

config &global_config() {
  static auto cfg = config{default_flags(), level::generic, ""};
  return cfg;
}

template <typename... Args>
void println(logger::context &ctx, const logger::config &cfg,
             const logger_internal::source_location &location,
             logger::level threshold, const std::string_view &format,
             Args &&...args) {
  const auto current_level_index = static_cast<std::uint8_t>(cfg.threshold);
  auto level_index = static_cast<std::uint8_t>(threshold);
  if (current_level_index < level_index) {
    return;
  }

  if ((cfg.flags & flag::locking) != flag::none) {
    while (ctx.lock.test_and_set(std::memory_order_relaxed)) {
    }
  }

  level_index =
      std::min(level_index,
               static_cast<std::uint8_t>(::logger_internal::num_levels)) -
      1;

  std::string_view bright_clr, dark_clr, reset_clr, internal_clr;
  if ((cfg.flags & flag::colors) != flag::none) {
    bright_clr = ::logger_internal::level_bright_color_lookup[level_index];
    dark_clr = ::logger_internal::level_dark_color_lookup[level_index];
    reset_clr = ::logger_internal::reset_color;
    internal_clr = ::logger_internal::internal_color;
  }

  auto wrote_prefix = false;
  auto &stream = threshold <= level::warn ? *ctx.err : *ctx.out;

  const auto print_prefix = [&](const auto &...values) {
    stream << '[' << bright_clr;
    ((stream << values), ...) << reset_clr << ']';
    wrote_prefix = true;
  };

  static constexpr auto needs_clock = flag::date | flag::time | flag::timestamp;
  if ((cfg.flags & needs_clock) != flag::none) {
    namespace chr = std::chrono;

    using clock = chr::system_clock;
    const auto now = clock::now();

    static constexpr auto needs_time = flag::date | flag::time;
    if ((cfg.flags & needs_time) != flag::none) {
      const auto time = clock::to_time_t(now);
      const auto local_time = std::localtime(&time);

      if ((cfg.flags & flag::date) != flag::none) {
        print_prefix(1'900 + local_time->tm_year, '-', 1 + local_time->tm_mon,
                     '-', local_time->tm_mday);
      }

      if ((cfg.flags & flag::time) != flag::none) {
        const auto truncated = std::chrono::system_clock::from_time_t(time);
        const auto millis =
            chr::duration_cast<chr::milliseconds>(now - truncated).count();

        print_prefix(local_time->tm_hour, ':', local_time->tm_min, ':',
                     local_time->tm_sec, '.', millis);
      }
    }

    if ((cfg.flags & flag::timestamp) != flag::none) {
      const auto timestamp =
          chr::duration_cast<chr::milliseconds>(now.time_since_epoch());
      print_prefix(timestamp.count());
    }
  }

  if ((cfg.flags & flag::level_name) != flag::none) {
    print_prefix(::logger_internal::level_names[level_index]);
  }

  if ((cfg.flags & flag::filename) != flag::none) {
    if ((cfg.flags & flag::line_number) != flag::none) {
      print_prefix(' ', location.file, ':', location.line);
    } else {
      print_prefix(location.file);
    }
  } else if ((cfg.flags & flag::line_number) != flag::none) {
    print_prefix(location.line);
  }

  if ((cfg.flags & flag::function_name) != flag::none) {
    print_prefix(location.function);
  }

  if ((cfg.flags & flag::thread_id) != flag::none) {
    print_prefix(std::this_thread::get_id());
  }

  if (not cfg.identifier.empty()) {
    print_prefix(cfg.identifier);
  }

  if (wrote_prefix) {
    stream << ' ';
  }

  ::logger_internal::print_format(stream, dark_clr, reset_clr, internal_clr,
                                  format, std::forward<Args>(args)...);
  stream << '\n';

  ctx.lock.clear();
}

template <typename... Args>
void println(const logger_internal::source_location &location,
             logger::level log_level, const std::string_view &format,
             Args &&...args) {
  println(global_context(), global_config(), location, log_level, format,
          std::forward<Args>(args)...);
}

template <typename... Args>
error<Args...>::error(std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location)
    : error(global_context(), global_config(), fmt, std::forward<Args>(args)...,
            location) {}

template <typename... Args>
error<Args...>::error(context &ctx, std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location)
    : error(ctx, global_config(), fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
error<Args...>::error(const config &cfg, std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location)
    : error(global_context(), cfg, fmt, std::forward<Args>(args)..., location) {
}

template <typename... Args>
error<Args...>::error(context &ctx, const config &cfg, std::string_view fmt,
                      Args &&...args,
                      const logger_internal::source_location &location) {
  println(ctx, cfg, location, level::error, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
warn<Args...>::warn(std::string_view fmt, Args &&...args,
                    const logger_internal::source_location &location)
    : warn(global_context(), global_config(), fmt, std::forward<Args>(args)...,
           location) {}

template <typename... Args>
warn<Args...>::warn(context &ctx, std::string_view fmt, Args &&...args,
                    const logger_internal::source_location &location)
    : warn(ctx, global_config(), fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
warn<Args...>::warn(const config &cfg, std::string_view fmt, Args &&...args,
                    const logger_internal::source_location &location)
    : warn(global_context(), cfg, fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
warn<Args...>::warn(context &ctx, const config &cfg, std::string_view fmt,
                    Args &&...args,
                    const logger_internal::source_location &location) {
  println(ctx, cfg, location, level::warn, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
info<Args...>::info(std::string_view fmt, Args &&...args,
                    const logger_internal::source_location &location)
    : info(global_context(), global_config(), fmt, std::forward<Args>(args)...,
           location) {}

template <typename... Args>
info<Args...>::info(context &ctx, std::string_view fmt, Args &&...args,
                    const logger_internal::source_location &location)
    : info(ctx, global_config(), fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
info<Args...>::info(const config &cfg, std::string_view fmt, Args &&...args,
                    const logger_internal::source_location &location)
    : info(global_context(), cfg, fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
info<Args...>::info(context &ctx, const config &cfg, std::string_view fmt,
                    Args &&...args,
                    const logger_internal::source_location &location) {
  println(ctx, cfg, location, level::info, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
log<Args...>::log(std::string_view fmt, Args &&...args,
                  const logger_internal::source_location &location)
    : log(global_context(), global_config(), fmt, std::forward<Args>(args)...,
          location) {}

template <typename... Args>
log<Args...>::log(context &ctx, std::string_view fmt, Args &&...args,
                  const logger_internal::source_location &location)
    : log(ctx, global_config(), fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
log<Args...>::log(const config &cfg, std::string_view fmt, Args &&...args,
                  const logger_internal::source_location &location)
    : log(global_context(), cfg, fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
log<Args...>::log(context &ctx, const config &cfg, std::string_view fmt,
                  Args &&...args,
                  const logger_internal::source_location &location) {
  println(ctx, cfg, location, level::log, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
debug<Args...>::debug(std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location)
    : debug(global_context(), global_config(), fmt, std::forward<Args>(args)...,
            location) {}

template <typename... Args>
debug<Args...>::debug(context &ctx, std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location)
    : debug(ctx, global_config(), fmt, std::forward<Args>(args)..., location) {}

template <typename... Args>
debug<Args...>::debug(const config &cfg, std::string_view fmt, Args &&...args,
                      const logger_internal::source_location &location)
    : debug(global_context(), cfg, fmt, std::forward<Args>(args)..., location) {
}

template <typename... Args>
debug<Args...>::debug(context &ctx, const config &cfg, std::string_view fmt,
                      Args &&...args,
                      const logger_internal::source_location &location) {
  println(ctx, cfg, location, level::debug, fmt, std::forward<Args>(args)...);
}

} // namespace logger
