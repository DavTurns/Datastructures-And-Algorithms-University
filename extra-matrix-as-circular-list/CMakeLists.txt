cmake_minimum_required(VERSION 3.24)
project(matrix_zirkular)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix_zirkular App.cpp ExtendedTest.cpp
        ExtendedTest.h
        Matrix.cpp
        Matrix.h
        ShortTest.cpp
        ShortTest.h)
