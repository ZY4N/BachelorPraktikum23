cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic")

project(tests)

add_executable(Google_Tests_run
        #include/logger_test_util.hpp
        #source/logger_test.cpp
        ../source/components/metadata.cpp
        ../source/modules/frame_exporters/kitti.cpp
        ../source/modules/metadata_transcoders/json.cpp
        source/arx_test.cpp
        source/distance_filtering_test.cpp
        source/frame_exporter_test.cpp
        source/metadata_json_test.cpp
        source/ros_time_conversion_test.cpp
        source/transform_conversion_test.cpp
)

find_package(catkin REQUIRED COMPONENTS
        rosbag
        roscpp
        rospy
        std_msgs
)

include_directories(
        include
        ../include
        ../source
        ../../common/include
        ../libraries/rapidjson/include
        ../libraries/span/include/tcb
        ${catkin_INCLUDE_DIRS}
)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(GTest REQUIRED)

target_link_libraries(Google_Tests_run ${catkin_LIBRARIES})
link_directories(${GTEST_LIBRARIES})
target_link_libraries(Google_Tests_run Eigen3::Eigen GTest::GTest GTest::Main)
target_link_libraries(Google_Tests_run -lstdc++ -lz)
