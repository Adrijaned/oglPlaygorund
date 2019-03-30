cmake_minimum_required(VERSION 3.12)
project(test1)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ../..)
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(test1 SHARED main.cpp)