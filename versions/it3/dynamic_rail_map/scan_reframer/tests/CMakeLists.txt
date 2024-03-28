cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic")

project(tests)

add_executable(Google_Tests_run
        ../include/util/logger.hpp
        source/logger_test.cpp
        include/logger_test_util.hpp
        ../include/helpers/ros_time_conversion.hpp
        source/ros_time_conversion_test.cpp
)

include_directories(
        include
        ../include
        ../source
        ../libraries/span/include/tcb
)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(GTest REQUIRED)
find_package(catkin REQUIRED COMPONENTS
        rosbag
        roscpp
        rospy
        std_msgs
)

target_link_libraries(Google_Tests_runy ${catkin_LIBRARIES})
link_directories(${GTEST_LIBRARIES})
target_link_libraries(Google_Tests_run Eigen3::Eigen GTest::GTest GTest::Main)
