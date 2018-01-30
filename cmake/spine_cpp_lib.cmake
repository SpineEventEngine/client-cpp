#spine-cpp lib
set(SOURCE_LIB_FILES
        src/actor_request_factory.cc
        src/command_factory.cc
        src/topic_factory.cc
        src/query_factory.cc
        src/actor_request_factory_params.cc)


set(CPP_SPINE_LIBRARY_NAME ${CMAKE_PROJECT_NAME}-${VERSION})
add_library(${CPP_SPINE_LIBRARY_NAME} STATIC ${SOURCE_LIB_FILES} ${spine_generated_files} )
add_dependencies(${CPP_SPINE_LIBRARY_NAME} spine_proto_dependency grpc_dependency protobuf_dependency)
