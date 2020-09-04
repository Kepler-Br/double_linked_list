cmake_minimum_required(VERSION 3.16)
project(double_linked_list C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)
add_library(double_linked_list src/double_linked_list.c)
