cmake_minimum_required(VERSION 3.24)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Bag)

add_executable(lab1
        App.cpp
        Bag.cpp
        Bag.h
        BagIterator.cpp
        BagIterator.h
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h)
