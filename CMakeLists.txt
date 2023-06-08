cmake_minimum_required(VERSION 3.25) #установка минимальной версии
set(CMAKE_CXX_STANDART 20) # задание переменных
project(Render) # создание проекта

add_executable(Render main.cpp tgaimage.h tgaimage.cpp)