cmake_minimum_required(VERSION 3.31)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BinaryTree main.cpp
        BinaryTree.tpp)

target_compile_options(BinaryTree PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(BinaryTree PRIVATE -fsanitize=address)