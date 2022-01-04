cmake_minimum_required(VERSION 3.1)
project(game)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(util)
add_subdirectory(sublibrary1)
add_subdirectory(Google_tests)

add_executable(game main.cpp)

target_link_libraries(game
        sub::util
        sub::lib1)