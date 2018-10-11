include_directories(${GRPC_DEPENDENCIES_DIR}/include)
include_directories(${PROTOBUF_DEPENDENCIES_DIR}/src)
include_directories(${GTest_INCLUDE_DIRS}/include)

set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${GRPC_DEPENDENCIES_DIR}/bins/opt)
set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${PROTOBUF_DEPENDENCIES_DIR}/src/.libs)
set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${GRPC_DEPENDENCIES_DIR}/bins/opt/protobuf)
set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${GTEST_DEPENDENCIES_DIR})

link_directories(${CMAKE_BINARY_DIR})
link_directories(${GRPC_DEPENDENCIES_DIR}/libs/opt)
link_directories(${PROTOBUF_DEPENDENCIES_DIR}/src/.libs)
link_directories(${GRPC_DEPENDENCIES_DIR}/libs/opt/protobuf)
link_directories(${GTEST_DEPENDENCIES_DIR})

find_program(GRPC_CPP_PLUGIN_EXE grpc_cpp_plugin)
find_program(PROTOC_EXE protoc)

if(NOT GRPC_CPP_PLUGIN_EXE)
    set(GRPC_CPP_PLUGIN_EXE ${GRPC_DEPENDENCIES_DIR}/bins/opt/grpc_cpp_plugin)
endif()

if(NOT PROTOC_EXE)
    set(PROTOC_EXE ${GRPC_DEPENDENCIES_DIR}/bins/opt/protobuf/protoc)
endif()

#POCO & Boost
find_path(Poco_INCLUDE_DIRS Poco/Poco.h)
find_path(Boost_INCLUDE_DIRS boost/shared_ptr.hpp)
find_path(GRPC_INCLUDE_DIRS grpc++/grpc++.h)
find_path(Protobuf_INCLUDE_DIRS google/protobuf/any.h)
find_path(GTest_INCLUDE_DIRS gtest/gtest.h)

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
if(GRPC_INCLUDE_DIRS)
    include_directories(${GRPC_INCLUDE_DIRS})
endif()
if(Protobuf_INCLUDE_DIRS)
    include_directories(${Protobuf_INCLUDE_DIRS})
endif()
if(GTest_INCLUDE_DIRS)
    include_directories(${GTest_INCLUDE_DIRS})
endif()

find_library(Poco_FOUNDATION_LIB NAMES PocoFoundation PocoFoundationd)
