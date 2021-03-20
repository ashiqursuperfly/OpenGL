cmake_minimum_required(VERSION 3.17)
project(Offline1)

set(CMAKE_CXX_STANDARD 11)

set(OpenGlLinkers -lglut -lGLU -lGL)
add_executable(Offline1 headers/1605103_vector.h headers/1605103_util.h headers/1605103_camera.h headers/1605103_bubble.h headers/1605103_rectangle.h headers/1605103_circle.h headers/1605103_gun.h headers/1605103_rotation.h 1605103_2.cpp)
target_link_libraries(Offline1 ${OpenGlLinkers})