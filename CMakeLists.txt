cmake_minimum_required(VERSION 3.8)
project(Lab_0)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp "sequence.h" listsequence.h unittest.h arraysequence.h)
add_executable(Lab_0 ${SOURCE_FILES})