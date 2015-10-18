cmake_minimum_required (VERSION 3.3)
project (Shard)

# Version number
set (Shard_VERSION_MAJOR 0)
set (Shard_VERSION_MINOR 0)
set (Shard_VERSION_PATCH 1)

add_executable(Shard src/core/main.cpp src/core/simplegame.cpp)
