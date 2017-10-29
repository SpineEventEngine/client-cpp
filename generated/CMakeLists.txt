cmake_minimum_required(VERSION 3.9)
include(ExternalProject)

set(SPINE_JAR_URL http://maven.teamdev.com/repository/spine-snapshots/io/spine/spine-client/0.9.71-SNAPSHOT/spine-client-0.9.71-20170929.140522-2-proto.jar)

ExternalProject_Add(spine_jar
        URL ${SPINE_JAR_URL}
        PREFIX spine
        DOWNLOAD_DIR spine
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        )



