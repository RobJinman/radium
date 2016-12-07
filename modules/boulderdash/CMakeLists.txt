cmake_minimum_required(VERSION 2.8)

project(boulderdash)

include_directories(include/public)
include_directories(include/private)
include_directories(../../radium/include/public)

# This module depends on the renderer module
include_directories(../renderer/include/public)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB_RECURSE SRCS src/*.cpp)
add_library(boulderdash SHARED ${SRCS})

set_target_properties(boulderdash
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../../radium/build/modules"
)
