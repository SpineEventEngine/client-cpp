#!/usr/bin/env bash
mkdir -p dependencies/spine
cd dependencies
curl -o spine.jar http://maven.teamdev.com/repository/spine-snapshots/io/spine/spine-client/0.10.1-SNAPSHOT/spine-client-0.10.1-20171019.131949-2-proto.jar
unzip spine.jar -d spine