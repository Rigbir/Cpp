cmake_minimum_required(VERSION 3.31)
project(String)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(String String.cpp
        String.h
        main.cpp)
add_executable(TestString main.cpp)

target_compile_options(String PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(String PRIVATE -fsanitize=address)
