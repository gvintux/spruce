cmake_minimum_required(VERSION 3.0)
project(spruce)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DEMU)
set(SOURCES layer.cpp led.cpp spruce.cpp main.cpp button.cpp button.h)
add_executable(spruce ${SOURCES})
