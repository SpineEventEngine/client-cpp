set(TEST_SRCS
        test/actor_request_factory_test.cc
        test/command_factory_test.cc
        test/query_factory_test.cc
        test/topic_factory_test.cc
        test/common_factory_test.h)

# proto
macro(compile_proto_file filename)
    get_filename_component(dirname ${filename} PATH)
    get_filename_component(basename ${filename} NAME_WE)
    add_custom_command(
            OUTPUT ${dirname}/${basename}.pb.cc
            DEPENDS ${PROTOC_EXE} ${filename}
            COMMAND ${PROTOC_EXE} ${filename}
            --cpp_out=${dirname}
            -I ${PROTO_DIR}
            -I ${dirname}
            VERBATIM
    )
endmacro(compile_proto_file)

set(test_proto_files
        ${CMAKE_SOURCE_DIR}/test/unit_tests.proto
        ${CMAKE_SOURCE_DIR}/test/unit_tests_no_prefix.proto)

set(test_generated_files)
foreach(proto_file ${test_proto_files})
    compile_proto_file(${proto_file})
    string(REPLACE .proto .pb.cc pb_file ${proto_file})
    set(test_generated_files ${test_generated_files} ${pb_file})
endforeach(proto_file)

add_executable(runTests ${TEST_SRCS} ${test_generated_files})

add_subdirectory(${GTEST_DEPENDENCIES_DIR} EXCLUDE_FROM_ALL)

find_library(PROTOBUF_LIB protobuf)
find_library(Poco_FOUNDATION_LIB NAMES PocoFoundation PocoFoundationd)

target_link_libraries(runTests gtest_main ${CPP_SPINE_LIBRARY_NAME}
        ${PROTOBUF_LIB}
        ${Poco_FOUNDATION_LIB}
        )
add_dependencies(runTests ${CPP_SPINE_LIBRARY_NAME})
