cmake_minimum_required(VERSION 3.19)
project(Offline2)

set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL)

add_executable(Offline2 headers/1605103_util.h headers/1605103_vector.h headers/1605103_matrix.h headers/1605103_input_handler.h main.cpp)