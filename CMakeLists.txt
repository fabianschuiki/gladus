cmake_minimum_required(VERSION 2.8)
project(gladus)

set(CMAKE_BUILD_TYPE Debug)

include_directories(.)
add_executable(compilation tests/compilation.cpp)

install(DIRECTORY gladus/ DESTINATION include/gladus)
