cmake_minimum_required(VERSION 3.5.1)
project(spine)

file (STRINGS "VERSION" VERSION)

set_source_files_properties(*.cc PROPERTIES LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

add_definitions(-std=gnu++14)
add_definitions(-fPIC)

#common libraries
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(cmake/dependencies.cmake)

include(cmake/spine_proto.cmake)
include(cmake/spine_cpp_lib.cmake)
