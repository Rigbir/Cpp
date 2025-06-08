cmake_minimum_required(VERSION 3.31)
project(Vector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Vector Vector.tpp
        Vector.h
        main.cpp)
add_executable(Test main.cpp)

target_compile_options(Vector PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(Vector PRIVATE -fsanitize=address)