cmake_minimum_required(VERSION 3.16)
project(scan_combiner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_CXX_COMPILER /usr/bin/gcc-10)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic -Werror -pthread -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/=")


add_executable(scan_combiner
        source/main.cpp
        source/module_interfaces/metadata_transcoding.ipp
        source/module_interfaces/frame_exportation.ipp
        source/module_interfaces/point_cloud_parsing.ipp
        source/modules/frame_exporters/kitti.cpp
        source/modules/frame_exporters/uos.cpp
        source/modules/metadata_transcoders/json.cpp
        source/modules/point_cloud_parsers/velodyne_lidar.ipp
        source/module_registration/metadata_transcoder_registration.ipp
        source/module_registration/point_cloud_parser_registration.ipp
        source/module_registration/frame_exporter_registration.ipp
        source/components/distance_filtering.ipp
        source/components/metadata.cpp
        source/components/reframer.cpp
        source/components/scan_combiner_pipeline.cpp
        source/components/unbagger.ipp
        source/components/unbagger.cpp
        source/components/chunker.cpp
        source/helpers/safe_rosbag.ipp
        source/helpers/ros_time_conversion.ipp
        source/helpers/ros_point_field_helpers.ipp
        source/helpers/transform_conversion.ipp
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
        source
        ../common/include
        libraries/span/include/tcb
        libraries/rapidjson/include
        ${catkin_INCLUDE_DIRS}
        SYSTEM Eigen
)

target_link_libraries(scan_combiner ${catkin_LIBRARIES})
target_link_libraries(scan_combiner Eigen3::Eigen)
target_link_libraries(scan_combiner -lm -lstdc++ -lpthread)

