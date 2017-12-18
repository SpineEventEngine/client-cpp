cmake_minimum_required(VERSION 3.9)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
#if (POLICY CMP0025)
#    cmake_policy(SET CMP0025 NEW)
#endif ()
project(spine)

file (STRINGS "VERSION" VERSION)

set_source_files_properties(*.cc PROPERTIES LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_definitions(-std=gnu++14)

find_package(POCO REQUIRED)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

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


include_directories(src)
include_directories(${Poco_INCLUDE_DIRS})
include_directories(${GENERATED_DIR})
include_directories(${GRPC_INSTALL_DIR}/include)

link_directories(${GRPC_INSTALL_DIR}/lib)


file(GLOB_RECURSE GENERATED_FILES ${GENERATED_DIR}/spine/*.pb.cc)

set(SOURCE_LIB_FILES
        src/common.cc
        src/common.h
        src/actor_request_factory.cc
        src/actor_request_factory.h
        src/command_factory.cc
        src/command_factory.h
        src/topic_factory.cc
        src/topic_factory.h
        src/query_factory.cc
        src/query_factory.h
        src/actor_request_factory_params.cc
        src/actor_request_factory_params.h)

set(TEST_SRCS
        test/actor_request_factory_test.cc test/common_test.cc)


set(LIBRARY_NAME ${CMAKE_PROJECT_NAME}-${VERSION})
add_library(${LIBRARY_NAME} STATIC ${SOURCE_LIB_FILES} ${GENERATED_FILES} )
add_dependencies(${LIBRARY_NAME} spine_generated)

#include(GoogleTest)
add_executable(runTests ${TEST_SRCS} )
target_link_libraries(runTests GTest::GTest GTest::Main ${LIBRARY_NAME} libprotobuf.a)

#gtest_add_tests(AllTests runTests)
#set_property(TARGET ${LIBRARY_NAME} PROPERTY CXX_STANDARD 14)
#set(CXX_STANDARD_REQUIRED true)