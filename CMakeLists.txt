cmake_minimum_required(VERSION 3.20)

# Project name and language
project(arbol VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include folder
include_directories(include)

# List all source files
set(SOURCES
    src/main.cpp
    include/ab.hpp
    include/abb.hpp
    include/abe.hpp
    include/nif.hpp
    include/nodob.hpp
    include/nodoavl.hpp
    include/avl.hpp
    include/test.hpp
)

# Create executable
add_executable(arbol ${SOURCES})

# Optional: compiler warnings
target_compile_options(arbol PRIVATE -Wall -Wextra -Wpedantic)