cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Snake)

add_executable(snake
    src/main.cpp
    src/game.cpp
    src/snake.cpp
    src/util.cpp
)

target_link_libraries(snake PUBLIC ncursesw)
target_include_directories(snake PRIVATE include)
