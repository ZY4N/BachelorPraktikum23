cmake_minimum_required(VERSION 3.16)
project(kitti2pcd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic -Werror -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/=")

add_executable(kitti2pcd
        source/converter.cpp
        include/converter.hpp
        source/main.cpp
        source/converter.ipp
)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(PCL 1.10 REQUIRED common io)

include_directories(
        source
        include
        ../common/include
        SYSTEM Eigen
        ${PCL_INCLUDE_DIRS}
)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
target_link_libraries(kitti2pcd Eigen3::Eigen ${PCL_LIBRARIES} -lm -lstdc++)
