cmake_minimum_required(VERSION 3.9)
project(spine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(PROTO_DIR ${CMAKE_HOME_DIRECTORY}/dependencies/spine)

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

file(GLOB_RECURSE SPINE_PROTO ${PROTO_DIR}/*.proto)

add_custom_target(spine_generated ALL)

foreach(proto_file ${SPINE_PROTO})
    add_custom_command(
            TARGET spine_generated
            COMMAND ${GRPC_INSTALL_DIR}/bin/protoc
            --cpp_out=${GENERATED_DIR}
            --grpc_out=${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${GRPC_INSTALL_DIR}/bin/grpc_cpp_plugin
            -I ${PROTO_DIR}
            ${proto_file}
            VERBATIM
    )
endforeach()


include_directories(${GENERATED_DIR})
include_directories(${GRPC_INSTALL_DIR}/include)
link_directories(${GRPC_INSTALL_DIR}/lib)


file(GLOB_RECURSE GENERATED_FILES ${GENERATED_DIR}/spine/*.pb.cc)

set(SOURCE_LIB_FILES
        src/common.cpp src/common.h)


add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_LIB_FILES} ${GENERATED_FILES} )
add_dependencies(${CMAKE_PROJECT_NAME} spine_generated)
