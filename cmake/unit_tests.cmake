enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SRCS
        test/actor_request_factory_test.cc
        test/command_factory_test.cc
        test/query_factory_test.cc
        )

add_executable(runTests ${TEST_SRCS} )

target_link_libraries(runTests GTest::GTest GTest::Main ${CPP_SPINE_LIBRARY_NAME}
        ${PROTOBUF_LIB}
        ${Poco_FOUNDATION_LIB}
        )
add_dependencies(runTests ${CPP_SPINE_LIBRARY_NAME})
