cmake_minimum_required(VERSION 2.8)

project(iz2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CC_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic -g3 -ggdb")


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")
include(CodeCoverage)
append_coverage_compiler_flags()

setup_target_for_coverage_lcov(
        NAME codeCoverage
        EXECUTABLE unit.out
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
        EXCLUDE "/usr/*" "${PROJECT_SOURCE_DIR}/src/main.c" "${PROJECT_SOURCE_DIR}/unit_tests/*"
)


set(MAIN src/main.c)
set(INC ./inc/)
set(LIN_PATH ./lib/linear/)
set(PRL_PATH ./lib/parallel/)


file(GLOB SRCS_LIN_LIB ${LIN_PATH}src/*.c)
file(GLOB SRCS_PRL_LIB ${PRL_PATH}src/*.c)
file(GLOB TESTS ${PROJECT_SOURCE_DIR}/unit_tests/*.cpp)

file(GLOB SRCS_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

list(REMOVE_ITEM SRCS_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

add_library(data_lib SHARED ${SRCS_COMMON})
target_include_directories(data_lib PUBLIC ${INC})

add_library(single_worker STATIC ${SRCS_LIN_LIB})
target_include_directories(single_worker PUBLIC ${LIN_PATH}/inc/ ${INC})
target_link_libraries(single_worker data_lib)

add_library(parallel_worker SHARED ${SRCS_PRL_LIB})
target_include_directories(parallel_worker PUBLIC ${PRL_PATH}/inc/ ${INC})
target_link_libraries(parallel_worker dl data_lib)

add_executable(main.out ${MAIN} ${SRCS_COMMON})
include_directories(main.out PUBLIC ${INC})
target_link_libraries(main.out PRIVATE single_worker parallel_worker dl)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(unit.out ${TESTS})
target_link_libraries(unit.out ${GTEST_LIBRARIES} data_lib single_worker parallel_worker -lpthread)

