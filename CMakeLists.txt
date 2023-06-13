cmake_minimum_required(VERSION 3.25) 
set(CMAKE_CXX_STANDART 20) 
project(Render) 
add_executable(Render main.cpp tgaimage.h tgaimage.cpp geometry.h geometry.cpp parser.cpp parser.h)