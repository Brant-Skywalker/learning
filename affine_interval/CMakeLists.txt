cmake_minimum_required(VERSION 3.22)
project(affine_interval)

set(CMAKE_CXX_STANDARD 20)

add_executable(affine_interval
        main.cpp
        interval.h
        interval.cpp
        affine.h
        affine.cpp
        )
