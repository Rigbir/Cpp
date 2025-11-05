cmake_minimum_required(VERSION 3.31)
project(Stack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Stack main.cpp
        Stack.tpp
)

target_compile_options(Stack PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(Stack PRIVATE -fsanitize=address)