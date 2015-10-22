cmake_minimum_required (VERSION 3.3 FATAL_ERROR)
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
include_directories(${GTEST_INCLUDE_DIRS})

# NCurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# Code coverage
include(CodeCoverage)
set(COVERAGE_FLAGS "--coverage")

# GLM
set(GLM_ROOT . CACHE PATH "Path to GLM")
include_directories(${GLM_ROOT})

# Compiler flags
set(CMAKE_C_FLAGS_DEBUG ${COVERAGE_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${COVERAGE_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${COVERAGE_FLAGS})

# Log level
add_definitions(-DLOG_LEVEL_DEBUG)

# Production code
set(MAIN_SRC src/core/main.cpp)

set(PRODUCTION_SRC 
    src/core/SimpleGame.cpp
    src/graphics/ASCIIRenderable.cpp
    src/graphics/ASCIIRenderingSystem.cpp
    src/graphics/CharBitmap.cpp
    src/graphics/NCursesRenderingSystem.cpp
    src/graphics/TestRenderable.cpp
    src/ncurses/ColorCache.cpp
    src/ncurses/NCursesInterface.cpp
    src/ncurses/NCursesException.cpp
    src/utility/BitPattern.cpp
    src/utility/StreamLogger.cpp
)

# Test code
set(TEST_SRC
    test/graphics/ASCIIRenderingSystemTest.cpp
    test/graphics/CharBitmapTest.cpp
    test/ncurses/ColorCacheTest.cpp
    test/utility/BitPatternTest.cpp
    test/utility/StreamLoggerTest.cpp
)

# Libraries
set(PRODUCTION_LIBRARIES ${CURSES_LIBRARIES})
set(TEST_LIBRARIES ${GTEST_BOTH_LIBRARIES} ${CURSES_LIBRARIES})

# C++ compile features
set(CXX_COMPILE_FEATURES cxx_nullptr)

# Main target
add_executable(Shard ${MAIN_SRC} ${PRODUCTION_SRC})
target_link_libraries(Shard ${PRODUCTION_LIBRARIES})
target_compile_features(Shard PRIVATE ${CXX_COMPILE_FEATURES})

# Test target
add_executable(RunTests ${TEST_SRC} ${PRODUCTION_SRC})
target_link_libraries(RunTests ${TEST_LIBRARIES})
target_compile_features(RunTests PRIVATE ${CXX_COMPILE_FEATURES})

# Coverage target
setup_target_for_coverage(coverage RunTests coverage '${CMAKE_CURRENT_SOURCE_DIR}/src/*')

# NCurses test app
add_executable(NCursesTestApp test/manual/NCursesTestApp.cpp ${PRODUCTION_SRC})
target_link_libraries(NCursesTestApp ${CURSES_LIBRARIES})
target_compile_features(NCursesTestApp PRIVATE ${CXX_COMPILE_FEATURES})
