cmake_minimum_required(VERSION 3.23)
project(dual_interval)

set(CMAKE_CXX_STANDARD 20)

add_executable(dual_interval
        main.cpp
        dual.h
        dual.cpp
        interval.h
        interval.cpp
        )
