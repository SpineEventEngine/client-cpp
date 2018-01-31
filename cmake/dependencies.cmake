include(ExternalProject)

set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/dependencies)
set(SPINE_DEPENDENCIES_DIR      ${DEPENDENCIES_DIR}/spine)
set(GRPC_DEPENDENCIES_DIR       ${DEPENDENCIES_DIR}/grpc)
set(PROTOBUF_DEPENDENCIES_DIR   ${GRPC_DEPENDENCIES_DIR}/third_party/protobuf)

set(GRPC_PREFIX_DIR ${CMAKE_BINARY_DIR}/grpc_dependency)
if(BUILD_DEPENDENCIES)
    # Spine proto files
    ExternalProject_Add(spine_proto_dependency
            URL http://maven.teamdev.com/repository/spine-snapshots/io/spine/spine-client/0.10.15-SNAPSHOT/spine-client-0.10.15-20171225.084237-2-proto.jar
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
            EXCLUDE_FROM_ALL 1
            SOURCE_DIR ${SPINE_DEPENDENCIES_DIR}
            )

    #gRPC
    execute_process(COMMAND curl -L https://grpc.io/release OUTPUT_VARIABLE GRPC_TAG)

    ExternalProject_Add(grpc_dependency
            PREFIX ${GRPC_PREFIX_DIR}
            SOURCE_DIR ${GRPC_DEPENDENCIES_DIR}
            UPDATE_COMMAND ""
            GIT_REPOSITORY "https://github.com/grpc/grpc.git"
            GIT_TAG "${GRPC_TAG}"
            GIT_SUBMODULES
            GIT_SHALLOW 1
            CONFIGURE_COMMAND ""
            BUILD_COMMAND make
            INSTALL_COMMAND ""
            EXCLUDE_FROM_ALL 1
            BUILD_IN_SOURCE 1
            TLS_VERIFY false
            )

    set(PROTOBUF_CONFIGURE_COMMAND "")
    if(NOT EXISTS "${PROTOBUF_DEPENDENCIES_DIR}/configure")
        set(PROTOBUF_CONFIGURE_COMMAND "./autogen.sh" COMMAND "./configure")
    endif()

    #Protobuf
    ExternalProject_Add(protobuf_dependency
            DEPENDS grpc_dependency
            DOWNLOAD_COMMAND ""
            SOURCE_DIR ${PROTOBUF_DEPENDENCIES_DIR}
            CONFIGURE_COMMAND COMMAND ${PROTOBUF_CONFIGURE_COMMAND}
            BUILD_COMMAND make
            INSTALL_COMMAND ""
            EXCLUDE_FROM_ALL 1
            BUILD_IN_SOURCE 1
            )
else()
    add_custom_target(spine_proto_dependency)
    add_custom_target(grpc_dependency)
    add_custom_target(protobuf_dependency)
endif()

include_directories(${GRPC_DEPENDENCIES_DIR}/include)
include_directories(${PROTOBUF_DEPENDENCIES_DIR}/src)

set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${GRPC_DEPENDENCIES_DIR}/bins/opt)
set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${PROTOBUF_DEPENDENCIES_DIR}/src/.libs)
set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${GRPC_DEPENDENCIES_DIR}/bins/opt/protobuf)

link_directories(${GRPC_DEPENDENCIES_DIR}/libs/opt)
link_directories(${PROTOBUF_DEPENDENCIES_DIR}/src/.libs)
link_directories(${GRPC_DEPENDENCIES_DIR}/libs/opt/protobuf)

set(GRPC_CPP_PLUGIN_EXE ${GRPC_DEPENDENCIES_DIR}/bins/opt/grpc_cpp_plugin)
set(PROTOC_EXE ${GRPC_DEPENDENCIES_DIR}/bins/opt/protobuf/protoc)

#POCO & Boost
find_path(Poco_INCLUDE_DIRS Poco/Poco.h)
find_path(Boost_INCLUDE_DIRS boost/shared_ptr.hpp)

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

find_library(PROTOBUF_LIB libprotobuf.a)
find_library(Poco_FOUNDATION_LIB NAMES PocoFoundation PocoFoundationd)
