cmake_minimum_required(VERSION 3.9.6)
project(spine)

option(BUILD_DEPENDENCIES "Try to download and build third party libraries" OFF)
option(LOAD_SPINE_PROTO_FILES, "Try to download only spine proto dependencies" OFF)
option(ENABLE_CODE_COVERAGE "Enable code coverage" OFF)

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

set(DEPENDENCIES_DIR            ${CMAKE_SOURCE_DIR}/dependencies)
set(SPINE_DEPENDENCIES_DIR      ${DEPENDENCIES_DIR}/spine)
set(GRPC_DEPENDENCIES_DIR       ${DEPENDENCIES_DIR}/grpc)
set(PROTOBUF_DEPENDENCIES_DIR   ${GRPC_DEPENDENCIES_DIR}/third_party/protobuf)
set(GTEST_DEPENDENCIES_DIR      ${GRPC_DEPENDENCIES_DIR}/third_party/googletest/googletest)
set(GRPC_PREFIX_DIR             ${CMAKE_BINARY_DIR}/grpc_dependency)

set(DEPENDENCIES_BUILD_DIR ${DEPENDENCIES_DIR}/_build)
configure_file(cmake/dependencies.cmake.in ${DEPENDENCIES_DIR}/CMakeLists.txt)

if(NOT EXISTS ${DEPENDENCIES_BUILD_DIR})
    file(MAKE_DIRECTORY ${DEPENDENCIES_BUILD_DIR})
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ..
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${DEPENDENCIES_BUILD_DIR})

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${DEPENDENCIES_BUILD_DIR})

include(cmake/dependencies.cmake)
include(cmake/spine_proto.cmake)
include(cmake/spine_cpp_lib.cmake)
include(cmake/unit_tests.cmake)
include(cmake/docs.cmake)
