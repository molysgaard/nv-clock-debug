cmake_minimum_required(VERSION 3.10)
project(nv-clock-debug C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(nv-clock-debug main.c)

install(TARGETS nv-clock-debug
        RUNTIME DESTINATION bin)
