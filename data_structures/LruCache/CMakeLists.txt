cmake_minimum_required(VERSION 3.31)
project(LruCache)

set(CMAKE_CXX_STANDARD 20)

add_executable(LruCache main.cpp
        LRUCache.h)

target_compile_options(LruCache PRIVATE -Wextra -Werror -fsanitize=address)
target_link_options(LruCache PRIVATE -fsanitize=address)