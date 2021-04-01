cmake_minimum_required(VERSION 2.8)

project(iz2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CC_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic -g3 -ggdb")

if ("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_lcov(
            NAME codeCoverage
            EXECUTABLE unit_default.out unit_parallel.out unit.out
            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
            EXCLUDE "/usr/*" "${PROJECT_SOURCE_DIR}/src/main.c" "${PROJECT_SOURCE_DIR}/unit_tests/*.cpp")
endif ()

set(MAIN src/main.c)
set(UNIT ./unit_tests)
set(INC ./inc/)
set(LIN_PATH ./lib/linear/)
set(PRL_PATH ./lib/parallel/)


file(GLOB SRCS_LIN_LIB ${LIN_PATH}src/*.c)
file(GLOB SRCS_PRL_LIB ${PRL_PATH}src/*.c)
file(GLOB TESTS_PRL ${PROJECT_SOURCE_DIR}/unit_tests/parallel/*.cpp)
file(GLOB TESTS_DEF ${PROJECT_SOURCE_DIR}/unit_tests/default/*.cpp)
file(GLOB TESTS_DATA_LIB ${PROJECT_SOURCE_DIR}/unit_tests/*.cpp)


file(GLOB SRCS_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

list(REMOVE_ITEM SRCS_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

add_library(data_lib SHARED ${SRCS_COMMON})
target_include_directories(data_lib PUBLIC ${INC})

add_library(single_worker STATIC ${SRCS_LIN_LIB})
target_include_directories(single_worker PUBLIC ${LIN_PATH}/.. ${INC})
target_link_libraries(single_worker data_lib)

add_library(parallel_worker SHARED ${SRCS_PRL_LIB})
target_include_directories(parallel_worker PUBLIC ${PRL_PATH}/.. ${INC})
target_link_libraries(parallel_worker dl data_lib)


add_executable(main_default.out ${MAIN})
include_directories(main_default.out PUBLIC ${INC} ${LIN_PATH}/..)
target_link_libraries(main_default.out PRIVATE single_worker)


add_executable(main_parallel.out ${MAIN})
include_directories(main_parallel.out PUBLIC ${INC} ${PRL_PATH}/..)
target_link_libraries(main_parallel.out PRIVATE parallel_worker dl)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unit.out ${TESTS_DATA_LIB})
target_include_directories(unit.out PUBLIC ${INC})
target_link_libraries(unit.out ${GTEST_LIBRARIES} data_lib pthread gtest)

add_executable(unit_default.out ${TESTS_DEF} ${UNIT}/tests.cpp)
target_include_directories(unit_default.out PUBLIC ${INC} ${UNIT})
target_link_libraries(unit_default.out ${GTEST_LIBRARIES} data_lib single_worker pthread gtest)

add_executable(unit_parallel.out ${TESTS_PRL} ${UNIT}/tests.cpp)
target_include_directories(unit_parallel.out PUBLIC ${INC} ${UNIT})
target_link_libraries(unit_parallel.out ${GTEST_LIBRARIES} data_lib parallel_worker -lpthread pthread gtest)

