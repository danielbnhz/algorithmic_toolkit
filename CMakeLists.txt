cmake_minimum_required(VERSION 3.30)
project(algorithmic_toolkit)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithmic_toolkit
        implementations/cpp/main.cpp
        implementations/cpp/sliding-window/sliding_window.cpp
        implementations/cpp/binary-search/binary_search.cpp
        implementations/cpp/sorting/quicksort.cpp
        implementations/cpp/utilities/input_utils.cpp
        implementations/cpp/utilities/input_utils.h)
