project(util)

add_library(${PROJECT_NAME} util.cpp)
add_library(sub::util ALIAS ${PROJECT_NAME})

target_include_directories(util
        PUBLIC
        ${PROJECT_SOURCE_DIR}
        )