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

find_path(Poco_INCLUDE_DIRS Poco/Poco.h)
find_path(Boost_INCLUDE_DIRS boost/shared_ptr.hpp)
find_path(Protobuf_INCLUDE_DIRS google/protobuf/message.h)
find_path(Grpc_INCLUDE_DIRS grpc++/grpc++.h)

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${Grpc_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(cmake/spine_proto.cmake)
include(cmake/spine_cpp_lib.cmake)

include(cmake/unit_tests.cmake)
