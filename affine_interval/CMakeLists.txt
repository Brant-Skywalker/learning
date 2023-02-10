cmake_minimum_required(VERSION 3.23)
project(affine_interval)

set(CMAKE_CXX_STANDARD 20)

add_executable(affine_interval
        main.cpp
        interval.h
        interval.cpp
        zonotope.h
        zonotope.cpp
        )
