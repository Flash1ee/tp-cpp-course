cmake_minimum_required(VERSION 2.8)

project(iz2)


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CC_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic -g3 -ggdb")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -g3 -ggdb")

set(MAIN src/main.c)
set(INC ./inc/)
set(LIN_PATH ./lib/linear/)
set(PRL_PATH ./lib/parallel/)


file(GLOB SRCS_LIN_LIB ${LIN_PATH}src/*.c)
file(GLOB SRCS_PRL_LIB ${PRL_PATH}src/*.c)

file(GLOB SRCS_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

list(REMOVE_ITEM SRCS_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)
#list(REMOVE_ITEM SOURCES_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_worker.c)

add_library(single_worker STATIC ${SRCS_LIN_LIB})
target_include_directories(single_worker PUBLIC ${LIN_PATH}/inc/ ${INC})

#list(REMOVE_ITEM SOURCES_LIB ${CMAKE_CURRENT_SOURCE_DIR}/src/default_worker.c)
add_library(parallel_worker SHARED ${SRCS_PRL_LIB})
target_include_directories(parallel_worker PUBLIC ${PRL_PATH}/inc/ ${INC})
target_link_libraries(parallel_worker dl)

add_executable(main.out ${MAIN} ${SRCS_COMMON})
include_directories(main.out PUBLIC ${INC})
target_link_libraries(main.out PRIVATE single_worker parallel_worker dl)
