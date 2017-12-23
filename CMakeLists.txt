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

find_package(Poco REQUIRED Foundation)
find_package(Boost REQUIRED)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include(spine-proto.cmake)



include_directories(src)
include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${GRPC_INSTALL_DIR}/include)

link_directories(${GRPC_INSTALL_DIR}/lib)


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
        src/actor_request_factory_params.h src/type_url.cc src/type_url.h)

set(TEST_SRCS
        test/actor_request_factory_test.cc
        test/common_test.cc test/type_url_test.cc)


set(LIBRARY_NAME ${CMAKE_PROJECT_NAME}-${VERSION})
add_library(${LIBRARY_NAME} STATIC ${SOURCE_LIB_FILES} ${spine_generated_files} )

add_executable(runTests ${TEST_SRCS} )
find_library(PROTOBUF_LIB libprotobuf.a)
target_link_libraries(runTests GTest::GTest GTest::Main ${LIBRARY_NAME}
        ${PROTOBUF_LIB}
        ${Poco_LIBRARIES})
add_dependencies(runTests ${LIBRARY_NAME})

find_package(Doxygen)
set(DOXYGEN_JAVADOC_AUTOBRIEF TRUE)
doxygen_add_docs(docs ${SOURCE_LIB_FILES})
