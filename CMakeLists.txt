cmake_minimum_required(VERSION 3.22)
project(database C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Werror -pedantic)

add_executable(database main.c table.c hashtable.c hashtable.h)
