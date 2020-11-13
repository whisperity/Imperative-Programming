cmake_minimum_required(VERSION 3.15)
project(Month C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(date)
add_subdirectory(month)
add_subdirectory(positional_nums)

add_executable(MonthMain
    main.c)
target_link_libraries(MonthMain
    date
    month
    positional_nums)
