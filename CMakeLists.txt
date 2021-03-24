cmake_minimum_required(VERSION 2.8)

project(iz2)


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CC_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic -g3 -ggdb")
set(MAIN src/main.c)

include_directories(./inc/)
file(GLOB SOURCES src/*.c)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

add_executable(main.out ${MAIN} ${SOURCES})