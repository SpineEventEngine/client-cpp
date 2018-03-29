cmake_minimum_required(VERSION 3.5.1)
project(todolist)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

add_definitions(-std=gnu++14)
add_definitions(-fPIC)

find_path(Poco_INCLUDE_DIRS Poco/Poco.h)
find_path(Boost_INCLUDE_DIRS boost/shared_ptr.hpp)
find_path(Protobuf_INCLUDE_DIRS google/protobuf/message.h)
find_path(Grpc_INCLUDE_DIRS grpc++/grpc++.h)

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${Grpc_INCLUDE_DIRS})

find_program(PROTOC_EXE protoc)  

include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(Protobuf_USE_STATIC_LIBS ON)

set(DEPENDENCIES_DIR            ${CMAKE_SOURCE_DIR}/dependencies)
set(DEPENDENCIES_BUILD_DIR ${DEPENDENCIES_DIR}/_build)
    
if(NOT EXISTS ${DEPENDENCIES_DIR})
    file(MAKE_DIRECTORY ${DEPENDENCIES_DIR})
    file(MAKE_DIRECTORY ${DEPENDENCIES_BUILD_DIR})
    configure_file(cmake/dependencies.cmake.in ${DEPENDENCIES_DIR}/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ..
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${DEPENDENCIES_BUILD_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${DEPENDENCIES_BUILD_DIR})
endif()

include_directories(${CPP_SPINE_LIB_INCLUDE_DIR})
include_directories(${CPP_SPINE_GENERATED_INCLUDE_DIR})

if(WIN32)
        set(CPP_SPINE_LIBRARY_NAME ${CPP_SPINE_LIBRARY_NAME})
        set(GRPC_LIBRARY_NAME grpc++.lib)
        set(PROTOBUF_LIB protobuf.lib)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")    
        add_definitions(-D_WIN32_WINNT=0x600)
else()
        set(CPP_SPINE_LIBRARY_NAME ${CPP_SPINE_LIBRARY_NAME})
        find_library(GRPC_LIBRARY_NAME libgrpc++.so)
        find_library(PROTOBUF_LIB libprotobuf.a)
        find_library(Poco_FOUNDATION_LIB NAMES PocoFoundation PocoFoundationd)
endif()

include_directories(third_party/tclap/tclap-1.2.1/include)

set(todolist_proto_files
        todolist/values.proto
        todolist/validation_rules.proto
        todolist/model.proto
        todolist/identifiers.proto
        todolist/changes.proto
        todolist/attributes.proto
        todolist/c/rejections.proto
        todolist/c/events.proto
        todolist/c/enrichments.proto
        todolist/c/commands.proto
        todolist/q/projections.proto
        )

set(Protobuf_IMPORT_DIRS ${Protobuf_IMPORT_DIRS} ${CMAKE_BINARY_DIR}/../../../dependencies/spine)

set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

set(PROTO_DIR ${CMAKE_HOME_DIRECTORY}/dependencies/model/todolist-model/model/src/main/proto/)

macro(compile_proto_file filename)
    get_filename_component(dirname ${filename} PATH)
    get_filename_component(basename ${filename} NAME_WE)
    add_custom_command(
            OUTPUT ${GENERATED_DIR}/${dirname}/${basename}.pb.cc
            DEPENDS ${PROTOC_EXE} ${PROTO_DIR}/${dirname}/${basename}.proto
            COMMAND ${PROTOC_EXE} ${PROTO_DIR}/${dirname}/${basename}.proto
            --proto_path=${Protobuf_IMPORT_DIRS}
            --cpp_out=${GENERATED_DIR}
            -I ${PROTO_DIR}
            VERBATIM
    )
endmacro(compile_proto_file)

set(todolist_generated_files)
foreach(proto_file ${todolist_proto_files})
    compile_proto_file(${proto_file})
    string(REPLACE .proto .pb.cc pb_file ${proto_file})
    set(todolist_generated_files ${todolist_generated_files} ${GENERATED_DIR}/${pb_file})
endforeach(proto_file)

include_directories(${GENERATED_DIR})
include_directories(${CMAKE_BINARY_DIR}/../)

set(todolist_source_files
        ${todolist_generated_files}
        src/todolist.cc
        command_handler/command_handler_impl.cc
        task_manager/task_runner.cc
        task_manager/task_completer.cc
        task_manager/todo_task.cc
        task_manager/list_task.cc
        task_manager/create_task.cc
        task_manager/create_task_label.cc
        console_view/console_view_impl.cc
        console_view/console_writer.cc
        task_manager/main_task.cc
        task_manager/create_simple_task.cc)

add_executable(${PROJECT_NAME} ${todolist_source_files})

set(TCLAP_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/third_party/tclap)

if(NOT EXISTS ${TCLAP_LIBRARY_DIR})
    file(MAKE_DIRECTORY ${TCLAP_LIBRARY_DIR})
    set(LOAD_THIRD_PARTY LOAD_THIRD_PARTY)
    add_custom_target(
        LOAD_THIRD_PARTY tar -xvzf ${CMAKE_SOURCE_DIR}/third_party/tclap-1.2.1.tar.gz -C ${TCLAP_LIBRARY_DIR}
    )
    add_dependencies(${PROJECT_NAME} ${LOAD_THIRD_PARTY})
endif()

target_link_libraries(todolist
        ${CPP_SPINE_LIBRARY_NAME}
        ${PROTOBUF_LIB}
        ${Poco_FOUNDATION_LIB}
        ${GRPC_LIBRARY_NAME}
        )
