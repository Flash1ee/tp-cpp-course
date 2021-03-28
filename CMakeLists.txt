cmake_minimum_required(VERSION 2.8)

project(iz2)


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CC_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic -g3 -ggdb")
set(MAIN src/main.c)
set(INC ./inc/)

file(GLOB SOURCES_LIB src/*.c)
list(REMOVE_ITEM SOURCES_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

add_library(single_worker STATIC ${SOURCES_LIB})
target_include_directories(single_worker PUBLIC ${INC})

add_executable(main.out ${MAIN})
include_directories(main.out PUBLIC ${INC})
target_link_libraries(main.out PRIVATE single_worker)