enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SRCS
        test/actor_request_factory_test.cc
        test/type_url_test.cc)

add_executable(runTests ${TEST_SRCS} )
find_library(PROTOBUF_LIB libprotobuf.a)
target_link_libraries(runTests GTest::GTest GTest::Main ${CPP_SPINE_LIBRARY_NAME}
        ${PROTOBUF_LIB}
        ${Poco_LIBRARIES})
add_dependencies(runTests ${CPP_SPINE_LIBRARY_NAME})
