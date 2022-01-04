project(util)

add_library(${PROJECT_NAME} util.cpp)
add_library(sub::util ALIAS ${PROJECT_NAME})

include_directories(${ROOT_DIR}/sublibrary1)

target_include_directories(util
        PUBLIC
        ${PROJECT_SOURCE_DIR}
        )