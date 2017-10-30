#!/usr/bin/env bash

echo "GRPC in $1"

mkdir -p .build
cd .build

cmake -DGRPC_INSTALL_DIR=$1 ..
cmake --build . -- -j5