cmake_minimum_required(VERSION 3.10)
project(drm_input_node)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic -Werror")

add_executable(drm_input_node
        source/main.cpp
        include/util/logger.hpp
        source/modules/unbagger.cpp
        include/modules/frame_exporter.hpp
        source/modules/frame_exporter.cpp
        include/helpers/transform_conversion.hpp
        include/modules/reframer.hpp
        source/modules/reframer.cpp
        source/modules/reframer.cpp
        include/modules/distance_filtering.hpp
        source/modules/distance_filtering.ipp
        include/lidar_parsers/parse_velodyne_lidar_points.hpp
        source/lidar_parsers/parse_velodyne_lidar_points.ipp
        include/helpers/ros_time_conversion.hpp
        include/helpers/ros_point_field_helpers.hpp
        source/helpers/ros_point_field_helpers.ipp
        include/helpers/safe_rosbag.hpp
        source/helpers/safe_rosbag.ipp
)

find_package(catkin REQUIRED COMPONENTS
        rosbag
        roscpp
        rospy
        std_msgs
)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)


include_directories(
        include
        libraries/span/include/tcb
        source
        ${catkin_INCLUDE_DIRS}
        SYSTEM Eigen
)

target_link_libraries(drm_input_node ${catkin_LIBRARIES})
target_link_libraries(drm_input_node Eigen3::Eigen)
target_link_libraries(drm_input_node -lstdc++)
