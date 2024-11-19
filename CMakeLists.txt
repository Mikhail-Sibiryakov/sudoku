cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_C_STANDARD 99)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(Vector src/Vector.c)
add_library(Matrix src/Matrix.c)

add_executable(Sudoku src/main.c)

target_link_libraries(Sudoku Vector Matrix)
