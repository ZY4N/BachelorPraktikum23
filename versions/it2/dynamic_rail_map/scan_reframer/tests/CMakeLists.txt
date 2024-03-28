cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wextra -pedantic")

project(tests)

add_executable(Google_Tests_run
        ../include/logger.hpp
        source/logger_test.cpp
        include/logger_test_util.hpp
)

include_directories(
        ../include
        include
)


find_package(GTest REQUIRED)
link_directories(${GTEST_LIBRARIES})
target_link_libraries(Google_Tests_run GTest::GTest GTest::Main)
