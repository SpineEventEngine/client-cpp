[![Travis Build Status](https://travis-ci.org/SpineEventEngine/client-cpp.svg?branch=master)](https://travis-ci.org/SpineEventEngine/client-cpp)
[![codecov](https://codecov.io/gh/SpineEventEngine/client-cpp/branch/master/graph/badge.svg)](https://codecov.io/gh/SpineEventEngine/client-cpp)
[![license](https://img.shields.io/badge/license-Apache%20License%202.0-blue.svg?style=flat)](http://www.apache.org/licenses/LICENSE-2.0)

# client-cpp
A client library for C++

## Pre-requisites

### Compiler
The library requires C++14 standard, thus GCC 5, or Clang 3.4 are required.

### Libraries
* [CMake](https://cmake.org/)
* [Boost](http://www.boost.org/)
* [POCO](https://pocoproject.org/)

#### Third party libraries and tools installation
##### Linux
    $ [sudo] apt-get install autoconf automake libtool build-essential  
    $ [sudo] apt-get install libboost-all-dev libpoco-dev libgflags-dev libgtest-dev curl unzip doxygen g++-5

##### Mac OS X
    $ [sudo] xcode-select --install
    $ [sudo] brew autoconf automake libtool build-essential
    $ [sudo] brew install libboost-all-dev libpoco-dev libgflags-dev libgtest-dev curl unzip doxygen g++-5

#### gRPC and Protobuf
Google's [gRPC](https://www.grpc.io) and [Protobuf](https://developers.google.com/protocol-buffers/) 
are the core components of the library, and the latest release versions should be present in the system
in order to build.

##### Linux
Linux does not have stable packages for gRPC and Protobuf with the latest versions, please prefer building from source. 

##### Mac OS X
    $ brew install --with-plugin grpc
    $ brew install protobuf
##### Building from Source
If you have troubles installing these libraries from the packaging system, you can build it from source.
Detailed instructions are on the websites for the libraries, or, you can set an option for the build, 
that will download and build gRPC and Protobuf (described in the Build section)     

## Build

Make a directory for build files, for example "_build", and run CMake

    $ mkdir -p _build && cd _build
    $ cmake ..
    $ cmake --build .
    
If you would like CMake to download and build gRPC and Protobuf from sources for you, replace 
`cmake ..` with `cmake -DBUILD_DEPENDENCIES=ON ..`.
This option is disabled by default to prevent 3rd-party build check everytime you build Spine.  
    
## Windows support
TBA    

