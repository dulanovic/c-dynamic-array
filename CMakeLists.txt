cmake_minimum_required(VERSION 3.10)
project(Dynamic_Array C)

set(CMAKE_C_STANDARD 11)

add_executable(Dynamic_Array src/main.c src/dynamic_array.c src/dynamic_array.h src/test_struct.c)
