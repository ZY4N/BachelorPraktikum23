#pragma once

#include <filesystem>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <system_error>

namespace drm {

/**
 * @brief A safe wrapper for the @c rosbag::Bag class that forwards errors using @c std::error_code.
 */
class safe_rosbag {
public:
	/**
	 * @brief Default constructor for the  @c safe_rosbag class.
	 */
	safe_rosbag() = default;

	/**
	 * @brief Open a ROS bag file.
	 *
	 * This method opens a ROS bag file specified by the provided file path using @c rosbag::Bag.
	 * If the opening process is successful, the method returns without errors. If an error occurs during the process,
	 * such as an exception thrown by rosbag, the method logs a warning and returns an error code indicating
	 * the nature of the issue.
	 *
	 * @param filename   The path to the ROS bag file to be opened.
	 *
	 * @return           An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] inline std::error_code open(const std::filesystem::path& filename) noexcept;

	/**
	 * @brief Get a view of the ROS bag.
	 *
	 * This method adds a query of the bag to the provided @c rosbag::View.
	 * If an error occurs during the process, such as an exception thrown by rosbag, the method
	 * logs a warning and returns an error code indicating the issue.
	 *
	 * @note             In case of an error, the provided @c rosbag::View may not be in a valid state,
	 *                   and its content should not be considered reliable.
	 *
	 * @param view       Reference to a @c rosbag::View object to store the obtained view.
	 * @param topic      The name of the topic to filter the view.
	 * @param min_time   The minimum timestamp of the desired time interval.
	 * @param max_time   The maximum timestamp of the desired time interval.
	 *
	 * @return           An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] inline std::error_code get_view(rosbag::View& view) noexcept;

	/**
	 * @brief Get a view of the ROS bag filtered by a specific topic.
	 *
	 * This method adds a query to the provided @c rosbag::View to filter messages by a specific topic.
	 * If an error occurs during the process, such as an exception thrown by rosbag, the method
	 * logs a warning and returns an error code indicating the issue.
	 *
	 * @note             In case of an error, the provided @c rosbag::View may not be in a valid state,
	 *                   and its content should not be considered reliable.
	 *
	 * @param view       Reference to a @c rosbag::View object to store the obtained view.
	 * @param topic      The name of the topic to filter the view.
	 * @param min_time   The minimum timestamp of the desired time interval.
	 * @param max_time   The maximum timestamp of the desired time interval.
	 *
	 * @return           An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] inline std::error_code get_topic_view(rosbag::View& view, const std::string& topic) noexcept;

	/**
	 * @brief Get a view of the ROS bag filtered by a specific topic within a specified time interval.
	 *
	 * This method adds a query to the provided @c rosbag::View to filter messages by a specific topic and time
	 * interval. If an error occurs during the process, such as an exception thrown by rosbag, the method logs a warning
	 * and returns an error code indicating the issue.
	 *
	 * @note             In case of an error, the provided @c rosbag::View may not be in a valid state,
	 *                   and its content should not be considered reliable.
	 *
	 * @param view       Reference to a @c rosbag::View object to store the obtained interval view.
	 * @param topic      The name of the topic to filter the view.
	 * @param min_time   The minimum timestamp of the desired time interval.
	 * @param max_time   The maximum timestamp of the desired time interval.
	 *
	 * @return           An @c std::error_code indicating the status of the operation.
	 */
	[[nodiscard]] inline std::error_code get_topic_interval_view(
		rosbag::View& view, const std::string& topic, const ros::Time& min_time, const ros::Time& max_time
	) noexcept;

	/**
	 * @brief Instantiate a message of type @c T from a @c rosbag::MessageInstance.
	 *
	 * This function template attempts to instantiate a message of the specified type @c T from the provided
	 * @c rosbag::MessageInstance. The instantiated message is stored in the provided @c boost::shared_ptr<T>.
	 * If the instantiation results in an exception or a nullptr, the error code is set
	 * and the @c msg_instance should not be used.
	 *
	 *
	 * @tparam T             The type of the message to be instantiated.
	 * @param msg            The @c rosbag::MessageInstance from which to instantiate the message.
	 * @param msg_instance   Reference to a @c boost::shared_ptr<T> to store the instantiated message instance.
	 *
	 * @return               An @c std::error_code indicating the status of the operation.
	 */
	template<typename T>
	[[nodiscard]] inline static std::error_code instantiate_msg(
		const rosbag::MessageInstance& msg, boost::shared_ptr<T>& msg_instance
	) noexcept;

	/**
	 * @brief Instantiate a message of type @c T from a @c rosbag::View::iterator.
	 *
	 * This function template attempts to instantiate a message of the specified type @c T from the provided
	 * @c rosbag::View::iterator. The instantiated message is stored in the provided @c boost::shared_ptr<T>.
	 * If the instantiation results in an exception or a nullptr, the error code is set
	 * and the @c msg_instance should not be used.
	 *
	 * @note                 Dereferencing a @c rosbag::View::iterator can lead to weird issues, so if you hold an
	 *                       @c rosbag::View::iterator use this function instead of dereferencing the iterator
	 *                       and calling @c instantiate_msg.
	 *
	 * @tparam T             The type of the message to be instantiated.
	 * @param msg_it         The  @c rosbag::View::iterator from which to instantiate the message.
	 * @param msg_instance   Reference to a @c boost::shared_ptr<T> to store the instantiated message instance.
	 *
	 * @return               An @c std::error_code indicating the status of the operation.
	 */
	template<typename T>
	[[nodiscard]] inline static std::error_code instantiate_msg_iterator(
		const rosbag::View::iterator& msg_it, boost::shared_ptr<T>& msg_instance
	) noexcept;

private:
	rosbag::Bag m_bag;
};

namespace safe_rosbag_error {

enum class codes {
	ok = 0,
	cannot_open_bag,
	cannot_open_view,
	message_instantiation_mismatch,
	message_instantiation_nullptr
};

struct category : std::error_category {
	[[nodiscard]] inline const char* name() const noexcept override;

	[[nodiscard]] inline std::string message(int ev) const override;
};

[[nodiscard]] inline std::error_code make_error_code(codes e) noexcept;

} // namespace safe_rosbag_error

} // namespace drm

[[nodiscard]] inline std::error_category& safe_rosbag_error_category() noexcept;

template<>
struct std::is_error_code_enum<drm::safe_rosbag_error::codes> : public std::true_type {};

#define INCLUDE_SAFE_ROSBAG_IMPLEMENTATION
#include "helpers/safe_rosbag.ipp"
#undef INCLUDE_SAFE_ROSBAG_IMPLEMENTATION
