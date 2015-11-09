cmake_minimum_required (VERSION 3.3 FATAL_ERROR)
project (Shard)

# Version number
set (Shard_VERSION_MAJOR 0)
set (Shard_VERSION_MINOR 0)
set (Shard_VERSION_PATCH 1)

# Log level
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DLOG_LEVEL_DEBUG)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

# Set compiler
set(CMAKE_CXX_COMPILER g++.exe)
set(CMAKE_C_COMPILER gcc.exe)

# Set custom CMake modules path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Dgtest_disable_pthreads=ON")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# Google mock (only debug mode)
set(BUILD_TESTS ON CACHE BOOL "Build the test target")
if (BUILD_TESTS)
    set (GMOCK_ROOT "" CACHE PATH "Path to Google Mock")
    set (GMOCK_INCLUDE_DIRS "${GMOCK_ROOT}/include")
    set (GMOCK_LIB ${GMOCK_ROOT}/libgmock.a)
    set (GMOCK_MAIN_LIB ${GMOCK_ROOT/libgmock_main.a})
    set (GMOCK_BOTH_LIBRARIES ${GMOCK_ROOT}/libgmock.a ${GMOCK_ROOT}/libgmock_main.a)
    include_directories(SYSTEM ${GMOCK_INCLUDE_DIRS})
endif (BUILD_TESTS)

# Google testing framework
if (BUILD_TESTS)
    set (GTEST_ROOT ${GMOCK_ROOT}/gtest)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
endif (BUILD_TESTS)

# SDL
set(FIND_SDL2_MANUALLY OFF CACHE BOOL "Locate SDL2 manually")
if (NOT FIND_SDL2_MANUALLY)
    find_package(SDL2 REQUIRED)
    include_directories(SYSTEM ${SDL2_INCLUDE_DIR})
    find_package(SDL2_ttf REQUIRED)
    include_directories(SYSTEM ${SDL2_TTF_INCLUDE_DIRS})
endif (NOT FIND_SDL2_MANUALLY)

if (FIND_SDL2_MANUALLY)
    set(SDL2_INCLUDE_DIR "" CACHE PATH "SDL2 include dir")
    set(SDL2_LIBRARY_DIR "" CACHE PATH "SDL2 library dir")
    set(SDL2_TTF_INCLUDE_DIR "" CACHE PATH "SDL2_ttf include dir")
    set(SDL2_TTF_LIBRARY_DIR "" CACHE PATH "SDL2_ttf library dir")
    include_directories(SYSTEM ${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIBRARY_DIR})
    include_directories(SYSTEM ${SDL2_TTF_INCLUDE_DIR})
    link_directories(${SDL2_TTF_LIBRARY_DIR})
    set(SDL2_LIBRARY -lmingw32 -lSDL2main -lSDL2)
    set(SDL2_TTF_LIBRARIES -lSDL2_ttf)
endif (FIND_SDL2_MANUALLY)

# Code coverage
if (BUILD_TESTS)
    include(CodeCoverage)
endif (BUILD_TESTS)

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


# Production code
set(MAIN_SRC src/core/main.cpp)

set(PRODUCTION_SRC 
    src/core/InvalidArgumentException.cpp
    src/core/InvalidFormatException.cpp
    src/core/RNG.cpp
    src/core/SimpleGame.cpp
    src/core/StringException.cpp
    src/graphics/ascii/sdl/SDLRenderingSystem.cpp
    src/graphics/ascii/ASCIIRenderable.cpp
    src/graphics/ascii/ASCIIRenderingSystem.cpp
    src/graphics/ascii/ASCIIFileRenderable.cpp
    src/graphics/ascii/ASCIISingleCharacterRenderable.cpp
    src/graphics/ascii/ASCIIWorldRenderer.cpp
    src/graphics/CharBitmap.cpp
    src/graphics/CharBitmapLoader.cpp
    src/input/SDLInputSystem.cpp
    src/logic/jobs/background/IncreaseThirst.cpp
    src/logic/jobs/background/PlayerControl.cpp
    src/logic/jobs/FindWater.cpp
    src/logic/jobs/Idle.cpp
    src/logic/jobs/Move.cpp
    src/logic/jobs/Wander.cpp
    src/logic/needs/Thirst.cpp
    src/logic/utility/EntityUtils.cpp
    src/logic/utility/GameObjectFactory.cpp
    src/logic/utility/GameObjectUtils.cpp
    src/logic/Entity.cpp
    src/logic/GameObject.cpp
    src/logic/World.cpp
    src/logic/WorldUpdater.cpp
    src/sdl/SDLInterface.cpp
    src/sdl/SDLTexture.cpp
    src/utility/algorithm/pathfinding/AStar.cpp
    src/utility/algorithm/Pathfinding.cpp
    src/utility/math/geometry/Box.cpp
    src/utility/math/Math.cpp
    src/utility/BitPattern.cpp
    src/utility/DateTime.cpp
    src/utility/LoggerFactory.cpp
    src/utility/StreamLogger.cpp
    src/utility/Variant.cpp
)

# Test code
set(TEST_SRC
    test/graphics/ascii/sdl/SDLRenderingSystemTest.cpp
    test/graphics/ascii/ASCIIRenderingSystemTest.cpp
    test/graphics/ascii/ASCIIWorldRendererTest.cpp
    test/graphics/CharBitmapTest.cpp
    test/graphics/CharBitmapLoaderTest.cpp
    test/graphics/RenderableStoreTest.cpp
    test/logic/jobs/background/IncreaseThirstTest.cpp
    test/logic/jobs/background/PlayerControlTest.cpp
    test/logic/jobs/FindWaterTest.cpp
    test/logic/jobs/MoveTest.cpp
    test/logic/jobs/WanderTest.cpp
    test/logic/needs/ThirstTest.cpp
    test/logic/utility/EntityUtilsTest.cpp
    test/logic/utility/GameObjectUtilsTest.cpp
    test/logic/EntityTest.cpp
    test/logic/GameObjectTest.cpp
    test/logic/WorldTest.cpp
    test/logic/WorldUpdaterTest.cpp
    test/utility/algorithm/pathfinding/AStarTest.cpp
    test/utility/math/geometry/BoxTest.cpp
    test/utility/math/MathTest.cpp
    test/utility/BitPatternTest.cpp
    test/utility/DateTimeTest.cpp
    test/utility/StreamLoggerTest.cpp
    test/utility/VariantTest.cpp
)

MESSAGE( STATUS "SDL2_LIBRARY: " ${SDL2_LIBRARY} )

# Libraries
set(PRODUCTION_LIBRARIES 
    ${CURSES_LIBRARIES} 
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
)

set(TEST_LIBRARIES 
    ${GTEST_BOTH_LIBRARIES} 
    ${GMOCK_BOTH_LIBRARIES} 
    ${CURSES_LIBRARIES} 
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARIES}
)

# Main target
add_executable(Shard ${MAIN_SRC} ${PRODUCTION_SRC})
target_link_libraries(Shard ${PRODUCTION_LIBRARIES})
target_compile_features(Shard PRIVATE ${CXX_COMPILE_FEATURES})

# Copy font into build directory
add_custom_command(TARGET Shard POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory
                       $<TARGET_FILE_DIR:Shard>/fonts)
add_custom_command(TARGET Shard POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:Shard>/fonts)

# Copy runtime dependencies into build directory
if (CMAKE_BUILD_TYPE MATCHES Release)

    add_custom_command(TARGET Shard POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_SOURCE_DIR}/lib $<TARGET_FILE_DIR:Shard>)

    MESSAGE( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
    add_custom_command(TARGET Shard POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E tar "cvf" "${CMAKE_BINARY_DIR}/Shard-${Shard_VERSION_MAJOR}.${Shard_VERSION_MINOR}.${Shard_VERSION_PATCH}.zip" --format=zip
           "${CMAKE_BINARY_DIR}/Shard.exe"
           "${CMAKE_BINARY_DIR}/libfreetype-6.dll"
           "${CMAKE_BINARY_DIR}/LICENSE.freetype.txt"
           "${CMAKE_BINARY_DIR}/LICENSE.zlib.txt"
           "${CMAKE_BINARY_DIR}/SDL2.dll"
           "${CMAKE_BINARY_DIR}/SDL2_ttf.dll"
           "${CMAKE_BINARY_DIR}/zlib1.dll"
           "${CMAKE_BINARY_DIR}/libwinpthread-1.dll"
           "${CMAKE_BINARY_DIR}/fonts")

endif (CMAKE_BUILD_TYPE MATCHES Release)

# Test target
if (BUILD_TESTS)
    add_executable(RunTests ${TEST_SRC} ${PRODUCTION_SRC})
    target_link_libraries(RunTests ${TEST_LIBRARIES})
    target_compile_features(RunTests PRIVATE ${CXX_COMPILE_FEATURES})
endif (BUILD_TESTS)

# Coverage target
if (BUILD_TESTS)
    setup_target_for_coverage(coverage RunTests coverage '${CMAKE_CURRENT_SOURCE_DIR}/src/*')
endif (BUILD_TESTS)

# NCurses test app
# add_executable(NCursesTestApp test/manual/NCursesTestApp.cpp ${PRODUCTION_SRC})
# target_link_libraries(NCursesTestApp ${CURSES_LIBRARIES})
# target_compile_features(NCursesTestApp PRIVATE ${CXX_COMPILE_FEATURES})

# Build test app
# add_executable(BuildTestApp test/manual/BuildTestApp.cpp)

# Keyboard input test app
#add_executable(SDLApp test/manual/SDLApp.cpp)
#target_link_libraries(SDLApp ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})
