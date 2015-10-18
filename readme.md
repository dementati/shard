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
4. Create a subdirectory called build and cd into it
5. Run cmake ..
6. Run make

## Build

1. Create a subdirectory in the project root called build
2. cd into the build directory
3. ccmake ..
4. Press c - Note: This might result in some errors about missing libraries, which you can disregard unless they persist through the next step.
5. Specify the path to the directory where you unzipped Google Test with the GTEST_ROOT variable.
6. Press c again
7. Press g
8. cmake ..
9. make

## Run 
From the build directory
* Run "make test" to run the tests
* Rub "./Shard" to run the game
