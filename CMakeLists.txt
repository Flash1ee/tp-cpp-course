cmake_minimum_required(VERSION 3.17)
project(hw_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(./inc/)

add_executable(hw_1
        src/main.c
        src/input.c
        src/grouping.c
        src/packing.c)
