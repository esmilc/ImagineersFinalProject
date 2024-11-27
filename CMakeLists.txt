cmake_minimum_required(VERSION 3.29)
project(ImagineersFinalProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImagineersFinalProject
    main.cpp
        user_io.cpp
        user_io.h
        build_sequence_heap.cpp
        build_sequence_heap.h
        file_parsing.h
)
