Shard project.

# How to set up a developer environment

## Requirements

* If on Windows, Cygwin.
* g++
* make
* Perl (for lcov)

## Install CMake

Go to https://cmake.org/download/#latest and download and install the latest stable release. If you're on a Unix-based system, you might wanna use a package manager. If you're on Windows, you can install it through Cygwin.

## Install Google Testing Framework and Google Mock

Google Test comes bundled with Google Mock

1. Download the latest release of gmock from https://code.google.com/p/googlemock/downloads/list
2. Unzip it to a directory of your choice
3. cd into the directory 
4. ```ccmake .```
5. Press c
6. If you're on Cygwin, turn the option "gtest_disable_pthreads" ON.
7. Press c and g
8. ```make```

## Install SDL2

1. Install SDL2
2. Install SDL2_ttf

Use a package manager or Cygwin, or build from source, (>=v5.9). CMake will attempt to locate SDL2 automatically. If that fails, contact a senior developer.

## Install GLM

1. Go to https://github.com/g-truc/glm/releases
2. If you're on Cygwin, download a 0.9.5 release. There's a bug in 0.9.6 and 0.9.7 that breaks GLM on Cygwin, disregard this if it's been fixed in a later version.
3. If you're on native *nix, download the latest release.
4. Unzip it anywhere.

## Cygwin only: Install lcov
1. Download http://downloads.sourceforge.net/ltp/lcov-1.12.tar.gz
2. Extract it to a directory of your choice
3. cd into it and run ```make install```

## Build

1. ```cd my/project/root```
2. ```mkdir build```
3. ```cd build```
4. ```ccmake ..```
5. Press c - Note: This might result in some errors about missing libraries, which you can disregard unless they persist through the next step.
6. Specify the path to the directory where you unzipped Google Mock with the GMOCK_ROOT variable.
7. Specify the path to the directory where you unzipped GLM with the GLM_ROOT variable.
8. Press c again
9. Press g
10. ```make```

## Run 
From the build directory
* ```./Shard``` to run the game
* ```make test``` to run the tests
* ```make coverage``` to run the test coverage analysis
