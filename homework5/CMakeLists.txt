cmake_minimum_required(VERSION 3.21)
project(homework5)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})

#add_executable(homework5
#        matrix.hpp main.cpp)
#add_executable(expand
#        expand2.cpp)

add_executable(task2 expand2.cpp )
add_executable(task1 homework.cpp )
add_executable(task4 main.cpp )
add_executable(task4_new expand4.cpp)
