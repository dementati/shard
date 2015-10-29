cmake_minimum_required (VERSION 3.3 FATAL_ERROR)
project (Shard)

# Version number
set (Shard_VERSION_MAJOR 0)
set (Shard_VERSION_MINOR 0)
set (Shard_VERSION_PATCH 1)

# Set compiler
set(CMAKE_CXX_COMPILER /usr/bin/g++.exe)
set(CMAKE_C_COMPILER /usr/bin/gcc.exe)

# Set custom CMake modules path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# C++ compile features
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -Dgtest_disable_pthreads=ON")

# Google mock
set (GMOCK_ROOT "" CACHE PATH "Path to Google Mock")
set (GMOCK_INCLUDE_DIRS "${GMOCK_ROOT}/include")
set (GMOCK_LIB ${GMOCK_ROOT}/libgmock.a)
set (GMOCK_MAIN_LIB ${GMOCK_ROOT/libgmock_main.a})
set (GMOCK_BOTH_LIBRARIES ${GMOCK_ROOT}/libgmock.a ${GMOCK_ROOT}/libgmock_main.a)
include_directories(SYSTEM ${GMOCK_INCLUDE_DIRS})

# Google testing framework
set (GTEST_ROOT ${GMOCK_ROOT}/gtest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

# NCurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# Code coverage
include(CodeCoverage)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")

# GLM
set(GLM_ROOT "" CACHE PATH "Path to GLM")
include_directories(SYSTEM ${GLM_ROOT})

# Debug symbols 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Warning flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O -Wall -Weffc++ -pedantic  \
    -pedantic-errors -Wextra -Wcast-align \
    -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
    -Wdisabled-optimization \
    -Werror -Wfloat-equal  -Wformat  -Wformat=2 \
    -Wformat-nonliteral -Wformat-security  \
    -Wformat-y2k \
    -Wimport  -Winit-self \
    -Winvalid-pch   \
    -Wlong-long -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute   \
    -Wmissing-include-dirs -Wmissing-noreturn \
    -Wpacked -Wparentheses  -Wpointer-arith \
    -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
    -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused \
    -Wunused-function  -Wunused-label  -Wunused-parameter \
    -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings")

# Log level
add_definitions(-DLOG_LEVEL_DEBUG)

# Production code
set(MAIN_SRC src/core/main.cpp)

set(PRODUCTION_SRC 
    src/core/InvalidArgumentException.cpp
    src/core/InvalidFormatException.cpp
    src/core/SimpleGame.cpp
    src/core/StringException.cpp
    src/graphics/ascii/ncurses/NCursesRenderingSystem.cpp
    src/graphics/ascii/ASCIIRenderable.cpp
    src/graphics/ascii/ASCIIRenderingSystem.cpp
    src/graphics/ascii/ASCIIFileRenderable.cpp
    src/graphics/ascii/ASCIIWorldRenderer.cpp
    src/graphics/CharBitmap.cpp
    src/graphics/CharBitmapLoader.cpp
    src/logic/jobs/Idle.cpp
    src/logic/needs/Thirst.cpp
    src/logic/Entity.cpp
    src/logic/World.cpp
    src/logic/WorldUpdater.cpp
    src/ncurses/ColorCache.cpp
    src/ncurses/NCursesInterface.cpp
    src/ncurses/NCursesException.cpp
    src/utility/BitPattern.cpp
    src/utility/DateTime.cpp
    src/utility/LoggerFactory.cpp
    src/utility/StreamLogger.cpp
)

# Test code
set(TEST_SRC
    test/graphics/ascii/ASCIIRenderingSystemTest.cpp
    test/graphics/ascii/ASCIIWorldRendererTest.cpp
    test/graphics/CharBitmapTest.cpp
    test/graphics/CharBitmapLoaderTest.cpp
    test/graphics/RenderableStoreTest.cpp
    test/logic/EntityTest.cpp
    test/logic/ThirstTest.cpp
    test/logic/WorldTest.cpp
    test/logic/WorldUpdaterTest.cpp
    test/ncurses/ColorCacheTest.cpp
    test/utility/BitPatternTest.cpp
    test/utility/DateTimeTest.cpp
    test/utility/StreamLoggerTest.cpp
    test/utility/VariantTest.cpp
)

# Libraries
set(PRODUCTION_LIBRARIES ${CURSES_LIBRARIES})
set(TEST_LIBRARIES ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} ${CURSES_LIBRARIES})


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

# Build test app
add_executable(BuildTestApp test/manual/BuildTestApp.cpp)
