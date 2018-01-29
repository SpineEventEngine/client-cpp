include(ExternalProject)

ExternalProject_Add(spine_proto_dependency
        URL http://maven.teamdev.com/repository/spine-snapshots/io/spine/spine-client/0.10.15-SNAPSHOT/spine-client-0.10.15-20171225.084237-2-proto.jar
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        EXCLUDE_FROM_ALL 1
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependencies/spine"
        )


EXEC_PROGRAM(COMMAND curl -L https://grpc.io/release OUTPUT_VARIABLE GRPC_TAG)

ExternalProject_Add(grpc_dependency
        GIT_REPOSITORY "https://github.com/grpc/grpc.git"
        #GIT_REPOSITORY "git@github.com:grpc/grpc.git"
        GIT_TAG "${GRPC_TAG}"
        GIT_SUBMODULES
        GIT_SHALLOW 1
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        EXCLUDE_FROM_ALL 1
        TLS_VERIFY false
        )