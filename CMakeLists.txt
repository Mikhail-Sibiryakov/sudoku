cmake_minimum_required(VERSION 3.10)
project(Sudoku)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

add_library(Vector src/Vector.c)
add_library(Matrix src/Matrix.c)
add_library(printHelpers src/printHelpers.c)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} Vector Matrix printHelpers)
