project(sublibrary1)

add_library(${PROJECT_NAME} src/figure.cpp src/game.cpp src/room.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

message(STATUS "cmake source dir is" ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/util)
target_include_directories( ${PROJECT_NAME}
        PUBLIC
#        sub::util
        ${CMAKE_SOURCE_DIR}/util
        ${PROJECT_SOURCE_DIR}/include)