Shard project.

# How to set up a developer environment

## Requirements

* If on Windows, Cygwin.
* g++
* make

## Install CMake

Go to https://cmake.org/download/#latest and download and install the latest stable release. If you're on a Unix-based system, you might wanna use a package manager. If you're on Windows, you can install it through Cygwin.

## Install Google Testing Framework

1. Download the latest release from https://github.com/google/googletest
2. Unzip it to a directory of your choice
3. cd into the directory 
4. Run "cmake . && make"

## Cygwin only: Install lcov
1. Download http://downloads.sourceforge.net/ltp/lcov-1.12.tar.gz
2. Extract it to a directory of your choice
3. cd into it and run "make install"

## Build

1. Create a subdirectory in the project root called build
2. cd into the build directory
3. ccmake ..
4. Press c - Note: This might result in some errors about missing libraries, which you can disregard unless they persist through the next step.
5. Specify the path to the directory where you unzipped Google Test with the GTEST_ROOT variable.
6. Press c again
7. Press g
8. make

## Run 
From the build directory
* Rub "./Shard" to run the game
* Run "make test" to run the tests
* Run "make coverage" to run the test coverage analysis
