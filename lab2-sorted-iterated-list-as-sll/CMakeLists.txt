cmake_minimum_required(VERSION 3.24)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(SortedIteratedList)

add_executable(lab2
        SortedIteratedList/App.cpp
        SortedIteratedList/ExtendedTest.cpp
        SortedIteratedList/ExtendedTest.h
        SortedIteratedList/ListIterator.cpp
        SortedIteratedList/ListIterator.h
        SortedIteratedList/ShortTest.cpp
        SortedIteratedList/ShortTest.h
        SortedIteratedList/SortedIteratedList.cpp
        SortedIteratedList/SortedIteratedList.h)
