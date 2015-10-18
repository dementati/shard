cmake_minimum_required (VERSION 3.3)
project (Shard)

# Version number
set (Shard_VERSION_MAJOR 0)
set (Shard_VERSION_MINOR 0)
set (Shard_VERSION_PATCH 1)

# Google testing framework
set (GTEST_ROOT . CACHE PATH "Path to Google Testing Framework")
enable_testing()
find_package(GTest REQUIRED)
MESSAGE( STATUS "GTEST_FOUND: " ${GTEST_FOUND} )
MESSAGE( STATUS "GTEST_INCLUDE_DIRS: " ${GTEST_INCLUDE_DIRS} )
include_directories(${GTEST_INCLUDE_DIRS})

# Add production code
add_executable(Shard src/core/main.cpp src/core/simplegame.cpp)

# Add test code
add_executable(ExampleTest test/exampletest.cpp)
target_link_libraries(ExampleTest ${GTEST_BOTH_LIBRARIES})
add_test(ExampleTest ExampleTest)
