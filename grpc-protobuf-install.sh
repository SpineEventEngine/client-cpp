#!/usr/bin/env bash
mkdir -p dependencies
cd dependencies

git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
cd grpc
git submodule update --init

cd third_party/protobuf
./autogen.sh
./configure
make
make install

cd ../..
make
make install
