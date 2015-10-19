cmake_minimum_required (VERSION 3.3)
project (Shard)

# Version number
set (Shard_VERSION_MAJOR 0)
set (Shard_VERSION_MINOR 0)
set (Shard_VERSION_PATCH 1)

# Set custom CMake modules path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# Google testing framework
set (GTEST_ROOT . CACHE PATH "Path to Google Testing Framework")
enable_testing()
find_package(GTest REQUIRED)
# MESSAGE( STATUS "GTEST_INCLUDE_DIRS: " ${GTEST_INCLUDE_DIRS} )
include_directories(${GTEST_INCLUDE_DIRS})

# Code coverage
include(CodeCoverage)
set(COVERAGE_FLAGS "--coverage")

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG ${COVERAGE_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${COVERAGE_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${COVERAGE_FLAGS})

# Add production code
add_executable(Shard src/core/main.cpp src/core/simplegame.cpp)

# Add test code
add_executable(ExampleTest test/exampletest.cpp)
target_link_libraries(ExampleTest ${GTEST_BOTH_LIBRARIES})
add_test(ExampleTest ExampleTest)

# Add coverage target
setup_target_for_coverage(coverage ExampleTest coverage '${CMAKE_CURRENT_SOURCE_DIR}/*')
