set(GTEST_DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/dependencies/gtest/)

# Download and unpack googletest at configure time.
configure_file(cmake/gtest_cmake.in ${GTEST_DEPENDENCIES_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${GTEST_DEPENDENCIES_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${GTEST_DEPENDENCIES_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${GTEST_DEPENDENCIES_DIR}/googletest-src
        ${GTEST_DEPENDENCIES_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

set(TEST_SRCS
        test/actor_request_factory_test.cc
        test/command_factory_test.cc
        test/query_factory_test.cc
        test/topic_factory_test.cc
        test/common_factory_test.h)

add_executable(runTests ${TEST_SRCS} )

target_link_libraries(runTests gtest_main ${CPP_SPINE_LIBRARY_NAME}
        ${PROTOBUF_LIB}
        ${Poco_FOUNDATION_LIB}
        )
add_dependencies(runTests ${CPP_SPINE_LIBRARY_NAME})
