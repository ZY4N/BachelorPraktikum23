cmake_minimum_required(VERSION 3.10)
project(drm_input_node)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic -Werror -g")

add_executable(drm_input_node
        source/main.cpp
        include/logger.hpp
        source/unbagger.cpp
        include/frame_exporter.hpp
        source/frame_exporter.cpp
        include/transform_conversion.hpp
        include/reframer.hpp
        source/reframer.cpp
        source/reframer.cpp
        source/frame_exporter.cpp
        include/distance_filtering.hpp
        source/distance_filtering.ipp
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
