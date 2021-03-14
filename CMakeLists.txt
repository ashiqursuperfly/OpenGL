cmake_minimum_required(VERSION 3.17)
project(Offline1)

set(CMAKE_CXX_STANDARD 14)

set(OpenGlLinkers -lglut -lGLU -lGL)
add_executable(Offline1 util.h demo.cpp)
# add_executable(Offline1 util.h camera.cpp)
target_link_libraries(Offline1 ${OpenGlLinkers})