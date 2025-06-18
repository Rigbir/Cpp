cmake_minimum_required(VERSION 3.31)
project(List)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(List main.cpp
        List.tpp
        List.h)

add_executable(TestList main.cpp)

target_compile_options(List PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(List PRIVATE -fsanitize=address)