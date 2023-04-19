cmake_minimum_required(VERSION 3.25)
project(IJCDU2 C)

set(CMAKE_C_STANDARD 11)

add_executable(IJCDU2 tail.c circular_buffer.c circular_buffer.h circular_buffer.c)
