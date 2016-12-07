cmake_minimum_required(VERSION 2.8)

project(radium)

include_directories(include/public)
include_directories(include/private)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB_RECURSE SRCS src/*.cpp)
add_executable(radium ${SRCS})

target_link_libraries(radium dl)
