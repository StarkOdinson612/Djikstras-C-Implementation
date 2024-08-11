cmake_minimum_required(VERSION 3.28)
project(Djikstra C)

set(CMAKE_C_STANDARD 23)

add_executable(Djikstra main.c
        src/vector.c
        include/utils.h
        src/utils.c
)
