cmake_minimum_required(VERSION 3.19)

project(gallery_renamer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gallery_renamer gallery_renamer.cpp)