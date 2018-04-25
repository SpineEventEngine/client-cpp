#spine-cpp lib
set(SOURCE_LIB_FILES
        src/actor_request_factory.cc
        src/command_factory.cc
        src/topic_factory.cc
        src/query_factory.cc
        src/actor_request_factory_params.cc
        src/util/any_utils.cc)

set(SOURCE_HEADER_FILES
        include/spine/util/any_utils.h
        include/spine/util/message_utils.hpp
        include/spine/actor_request_factory.h
        include/spine/actor_request_factory_params.h
        include/spine/command_factory.h
        include/spine/query_factory.h
        include/spine/topic_factory.h
        include/spine/types.h
        include/spine/util/target_utils.hpp)


set(CPP_SPINE_LIBRARY_NAME ${CMAKE_PROJECT_NAME}-${VERSION})
add_library(${CPP_SPINE_LIBRARY_NAME} STATIC ${SOURCE_LIB_FILES} ${SOURCE_HEADER_FILES} ${spine_generated_files} )
