#!/usr/bin/env bash

mkdir -p _build
cd _build

mkdir -p generated
cd generated
cmake ../../generated
cmake --build .
cd ..

cmake -DGRPC_SRC_DIR=$1 ..
cmake --build . -- -j5