cmake_minimum_required(VERSION 3.25)
project(Djikstra C)

set(CMAKE_C_STANDARD 23)

set(SRCS
    src/vector.c
    src/utils.c
    src/priority_queue.c
    main.c
)

find_library(MATH_LIBRARY m)

add_executable(Djikstra ${SRCS})
target_link_libraries(Djikstra PUBLIC ${MATH_LIBRARY})
target_include_directories( Djikstra PUBLIC ./include/)



