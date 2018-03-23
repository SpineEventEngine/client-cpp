set(TEST_SRCS
        test/actor_request_factory_test.cc
        test/command_factory_test.cc
        test/query_factory_test.cc
        test/topic_factory_test.cc
        test/common_factory_test.h
        test/actor_request_factory_params_test.cc)

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

if(ENABLE_CODE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_executable(runTests ${TEST_SRCS} ${test_generated_files})

if(BUILD_DEPENDENCIES)
    add_subdirectory(${GTEST_DEPENDENCIES_DIR} EXCLUDE_FROM_ALL)
    target_link_libraries(runTests gtest_main ${CPP_SPINE_LIBRARY_NAME}
        libprotobuf.a
	${Poco_FOUNDATION_LIB}
	)
else()
    target_link_libraries(runTests gtest gtest_main pthread ${CPP_SPINE_LIBRARY_NAME}
        libprotobuf.a
        ${Poco_FOUNDATION_LIB}
        )
endif()
add_dependencies(runTests ${CPP_SPINE_LIBRARY_NAME})
