cmake_minimum_required(VERSION 3.10)
project(VectorEditorDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(vector_editor
    src/main.cpp
)

