cmake_minimum_required(VERSION 3.31)
project(SFINAE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(SFINAE main.cpp)

target_compile_options(SFINAE PRIVATE -Wextra -Werror)