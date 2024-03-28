#ifndef INCLUDE_SAFE_ROSBAG_IMPLEMENTATION
#	error Never include this file directly include 'safe_rosbag.hpp'
#endif

#include "util/logger.hpp"

#include <rosbag/view.h>

namespace drm {

const char* safe_rosbag_error::category::name() const noexcept {
	return "unbagger";
}

std::string safe_rosbag_error::category::message(const int ev) const {
	switch (static_cast<codes>(ev)) {
	case codes::ok:
		return "Ok";
	case codes::cannot_open_bag:
		return "An exception occurred while opening the rosbag. Look at the log to learn more.";
	case codes::cannot_open_view:
		return "An exception occurred while opening the view. Look at the log to learn more.";
	case codes::message_instantiation_mismatch:
		return "An exception occurred while instantiating the message. Look at the log to learn more.";
	case codes::message_instantiation_nullptr:
		return "The instantiated message points to null.";
	default:
		using namespace std::string_literals;
		return "unrecognized error ("s + std::to_string(ev) + ")";
	}
}
} // namespace drm

std::error_category& safe_rosbag_error_category() noexcept {
	static drm::safe_rosbag_error::category category;
	return category;
}

namespace drm {
std::error_code safe_rosbag_error::make_error_code(const codes e) noexcept {
	return { static_cast<int>(e), safe_rosbag_error_category() };
}

std::error_code safe_rosbag::open(const std::filesystem::path& filename) noexcept {
	using ec = safe_rosbag_error::codes;
	using safe_rosbag_error::make_error_code;
	auto error = std::error_code{};

	try {
		m_bag.open(filename, rosbag::bagmode::Read);
	} catch (const std::exception& e) {
		logger::warn("Error occurred while opening bag from %: %", filename, e.what());
		error = make_error_code(ec::cannot_open_bag);
	} catch (...) {
		logger::warn("Unknown error occurred while opening bag from %.", filename);
		error = make_error_code(ec::cannot_open_bag);
	}

	return error;
}

std::error_code safe_rosbag::get_view(rosbag::View& view) noexcept {
	using ec = safe_rosbag_error::codes;
	using safe_rosbag_error::make_error_code;
	auto error = std::error_code{};

	try {
		view.addQuery(m_bag);
	} catch (const std::exception& e) {
		logger::warn("Error occurred while opening view: %", e.what());
		error = make_error_code(ec::cannot_open_view);
	} catch (...) {
		logger::warn("Unknown error occurred while opening view.");
		error = make_error_code(ec::cannot_open_view);
	}

	return error;
}

std::error_code safe_rosbag::get_topic_view(rosbag::View& view, const std::string& topic) noexcept {
	using ec = safe_rosbag_error::codes;
	using safe_rosbag_error::make_error_code;
	auto error = std::error_code{};

	try {
		view.addQuery(m_bag, rosbag::TopicQuery(topic));
	} catch (const std::exception& e) {
		logger::warn("Error occurred while opening topic view: %", e.what());
		error = make_error_code(ec::cannot_open_view);
	} catch (...) {
		logger::warn("Unknown error occurred while opening topic view");
		error = make_error_code(ec::cannot_open_view);
	}

	return error;
}

std::error_code safe_rosbag::get_topic_interval_view(
	rosbag::View& view, const std::string& topic, const ros::Time& min_time, const ros::Time& max_time
) noexcept {
	using ec = safe_rosbag_error::codes;
	using safe_rosbag_error::make_error_code;
	auto error = std::error_code{};

	try {
		view.addQuery(m_bag, rosbag::TopicQuery(topic), min_time, max_time);
	} catch (const std::exception& e) {
		logger::warn("Error while occurred opening interval view of topic '%': %", topic, e.what());
		return ec::cannot_open_view;
	} catch (...) {
		logger::warn("Unknown error occurred while opening interval view of topic '%'.", topic);
		return ec::cannot_open_view;
	}

	return error;
}

template<typename T>
std::error_code safe_rosbag::instantiate_msg_iterator(
	const rosbag::View::iterator& msg_it, boost::shared_ptr<T>& msg_instance
) noexcept {
	using ec = safe_rosbag_error::codes;
	using safe_rosbag_error::make_error_code;
	auto error = std::error_code{};

	try {
		msg_instance = msg_it->instantiate<T>();
		if (not msg_instance) {
			error = ec::message_instantiation_nullptr;
		}
	} catch (const std::exception& e) {
		logger::warn("Error occurred while instantiating message: %", e.what());
		error = ec::message_instantiation_mismatch;
	} catch (...) {
		logger::warn("Unknown error occurred while instantiating message.");
		error = ec::message_instantiation_mismatch;
	}

	return error;
}

template<typename T>
std::error_code safe_rosbag::instantiate_msg(
	const rosbag::MessageInstance& msg, boost::shared_ptr<T>& msg_instance
) noexcept {
	using ec = safe_rosbag_error::codes;
	using safe_rosbag_error::make_error_code;
	auto error = std::error_code{};

	try {
		msg_instance = msg.template instantiate<T>();
		if (not msg_instance) {
			error = ec::message_instantiation_nullptr;
		}
	} catch (const std::exception& e) {
		logger::warn("Error occurred while instantiating message: %", e.what());
		error = ec::message_instantiation_mismatch;
	} catch (...) {
		logger::warn("Unknown error occurred while instantiating message.");
		error = ec::message_instantiation_mismatch;
	}

	return error;
}

} // namespace drm
