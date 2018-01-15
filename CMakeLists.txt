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

include_directories(include)
include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

include(cmake/code_coverage.cmake)
include(cmake/spine_proto.cmake)

include_directories(${GRPC_INSTALL_DIR}/include)
link_directories(${GRPC_INSTALL_DIR}/lib)

include(cmake/spine_cpp_lib.cmake)

include(cmake/unit_tests.cmake)
include(cmake/docs.cmake)

add_subdirectory(examples/hello_world)
