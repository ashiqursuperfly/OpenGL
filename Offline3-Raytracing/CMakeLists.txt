cmake_minimum_required(VERSION 3.17)
project(Offline3)

set(CMAKE_CXX_STANDARD 11)

# TODO: sudo apt install freeglut3-dev

set(OpenGlLinkers -lglut -lGLU -lGL)
add_executable(Offline3 headers/1605103_vector.h headers/1605103_util.h headers/1605103_opengl_util.h headers/1605103_camera.h headers/1605103_objects.h headers/1605103_ray_tracing.h main.cpp)
target_link_libraries(Offline3 ${OpenGlLinkers})