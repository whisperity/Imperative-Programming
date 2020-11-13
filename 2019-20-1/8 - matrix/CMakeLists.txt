cmake_minimum_required(VERSION 3.15)
project(matrix C)

set(CMAKE_C_STANDARD 99)

include_directories(matrix)

add_library(matrix SHARED
    matrix/matrix_io.c
    matrix/matrix_mem.c)

add_library(matrix_algorithm SHARED
    matrix/algorithm/determinant.c)

add_executable(main
    main.c)
target_link_libraries(main PUBLIC
    matrix matrix_algorithm)
