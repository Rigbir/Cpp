cmake_minimum_required(VERSION 3.31)
project(Queue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Queue main.cpp
        Queue.tpp
)

target_compile_options(Queue PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(Queue PRIVATE -fsanitize=address)