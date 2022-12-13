cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the project name
project(Snake)

add_executable(snake
    src/main.cpp
)

target_link_libraries(snake PUBLIC ncurses)
#target_include_directories(snake PRIVATE)
