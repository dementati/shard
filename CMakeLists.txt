cmake_minimum_required (VERSION 3.3 FATAL_ERROR)
project (Shard CXX)

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

# Production code
set(MAIN_SRC src/core/main.cpp)

set(PRODUCTION_SRC 
    src/core/simplegame.cpp
    src/utility/defaultlogger.cpp
)

# Test code
set(TEST_SRC
    test/utility/defaultloggertest.cpp
)

# C++ compile features
set(CXX_COMPILE_FEATURES cxx_nullptr)

# Main target
add_executable(Shard ${MAIN_SRC} ${PRODUCTION_SRC})
target_compile_features(Shard PRIVATE ${CXX_COMPILE_FEATURES})

# Test target
add_executable(RunTests ${TEST_SRC} ${PRODUCTION_SRC})
target_link_libraries(RunTests ${GTEST_BOTH_LIBRARIES})
target_compile_features(RunTests PRIVATE ${CXX_COMPILE_FEATURES})

# Coverage target
setup_target_for_coverage(coverage RunTests coverage '${CMAKE_CURRENT_SOURCE_DIR}/src/*')
