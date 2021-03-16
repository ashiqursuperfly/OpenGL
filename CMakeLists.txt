cmake_minimum_required(VERSION 3.17)
project(Offline1)

set(CMAKE_CXX_STANDARD 11)

set(OpenGlLinkers -lglut -lGLU -lGL)
add_executable(Offline1 headers/vector.h headers/util.h headers/camera.h headers/bubble.h headers/rectangle.h headers/circle.h headers/gun.h gun.cpp)
target_link_libraries(Offline1 ${OpenGlLinkers})