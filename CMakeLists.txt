cmake_minimum_required(VERSION 3.26)
project(CPP1_s21_matrixplus_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(code-samples)
include_directories(src)

add_executable(CPP1_s21_matrixplus_1

        src/s21_matrix_oop.cpp
        src/s21_matrix_oop.h)
