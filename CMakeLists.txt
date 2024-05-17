cmake_minimum_required(VERSION 3.27)
project(C_project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_project
        cdataframe.c
        cdataframe.h
        main.c)
