cmake_minimum_required(VERSION 3.10)
project(sublibrary1)

include_directories(${PROJECT_SOURCE_DIR}/util)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} src/figure.cpp src/game.cpp src/room.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

add_subdirectory(util)

message(STATUS "project source dir is" ${PROJECT_SOURCE_DIR}/util)

#target_include_directories( ${PROJECT_NAME}
#        PUBLIC
#        ${PROJECT_SOURCE_DIR}/util)