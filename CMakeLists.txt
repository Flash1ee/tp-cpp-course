cmake_minimum_required(VERSION 3.16)
project(hw_1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDART 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -g3 -ggdb")
set(CMAKE_CXX_COMPILER "g++")

include_directories(./inc/)

add_library(WORK_LIB STATIC src/grouping.c src/input.c src/packing.c)
target_include_directories(WORK_LIB PUBLIC ./inc)
set_target_properties(WORK_LIB PROPERTIES PUBLIC_HEADER inc/*.h)

set(MAIN src/main.c)
set(TESTS unit_tests/tests.cpp)

add_executable(main.out ${MAIN})
target_include_directories(main.out PUBLIC ./inc/)
target_link_libraries(main.out WORK_LIB)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message(${GTEST_INCLUDE_DIRS})
add_executable(unit.out ${TESTS})
target_include_directories(unit.out PUBLIC ./inc/)
target_link_libraries(unit.out WORK_LIB ${GTEST_LIBRARIES} -lpthread)

