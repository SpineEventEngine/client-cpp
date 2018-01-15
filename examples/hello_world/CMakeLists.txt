cmake_minimum_required(VERSION 3.9)
project(hello-world)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

add_definitions(-std=gnu++14)
add_definitions(-fPIC)

find_package(Poco REQUIRED Foundation)
find_package(Boost REQUIRED)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(Protobuf_USE_STATIC_LIBS ON)

#grpc
include_directories(${GRPC_INSTALL_DIR}/include)
link_directories(${GRPC_INSTALL_DIR}/lib)

#spine-cpp
include_directories(../../include)
include_directories(../../_build/generated)
link_directories(../../_build)
set(CPP_SPINE_LIBRARY_NAME libspine-0.10.0.a)

include_directories(${CMAKE_BINARY_DIR})

#proto
set(Protobuf_IMPORT_DIRS ${Protobuf_IMPORT_DIRS} dependencies/spine)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS model/src/main/proto/hello.proto)



set(hello-world_SRC
        ${PROTO_SRCS}
        cpp-client-sender/main_sender.cc
        )

add_executable(hello-world ${hello-world_SRC})
target_link_libraries(hello-world
        ${CPP_SPINE_LIBRARY_NAME}
        ${Protobuf_LIBRARIES}
        ${Poco_LIBRARIES}
        libgrpc++.a
        )



set(hello-world-reader_SRC
        ${PROTO_SRCS}
        cpp-client-reader/main_receiver.cc
        )

add_executable(hello-world-reader ${hello-world-reader_SRC})
target_link_libraries(hello-world-reader
        ${CPP_SPINE_LIBRARY_NAME}
        ${Protobuf_LIBRARIES}
        ${Poco_LIBRARIES}
        libgrpc++.a
        )
