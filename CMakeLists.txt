cmake_minimum_required(VERSION 3.9)
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
find_package(Poco REQUIRED Foundation)
find_package(Boost REQUIRED)

find_package(Protobuf REQUIRED)
set(Protobuf_USE_STATIC_LIBS ON)

include_directories(include)
include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    add_definitions(-D_WIN32_WINNT=0x600)  
endif()

include(cmake/code_coverage.cmake)
include(cmake/spine_proto.cmake)

include(cmake/spine_cpp_lib.cmake)

include(cmake/unit_tests.cmake)
include(cmake/docs.cmake)

add_subdirectory(examples/hello_world)
add_subdirectory(examples/todolist)
