cmake_minimum_required(VERSION 3.31)
project(Unique_ptr)

set(CMAKE_CXX_STANDARD 20)

add_executable(Unique_ptr main.cpp)

add_executable(Test main.cpp)

target_compile_options(Unique_ptr PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(Unique_ptr PRIVATE -fsanitize=address)