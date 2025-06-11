cmake_minimum_required(VERSION 3.31)
project(Figures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Figures Figures.cpp,
                       Figures.h
                       main.cpp)

add_executable(TestFigures main.cpp)

target_compile_options(Figures PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(Figures PRIVATE -fsanitize=address)
