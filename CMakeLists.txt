cmake_minimum_required(VERSION 2.8)
project(gladus)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)

include_directories(. ${OPENGL_INCLUDE_DIRS})
add_executable(compilation tests/compilation.cpp)
target_link_libraries(compilation ${OPENGL_LIBRARIES})

install(DIRECTORY gladus/ DESTINATION include/gladus)
