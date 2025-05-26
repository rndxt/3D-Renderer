cmake_minimum_required(VERSION 3.11)
project(3D-Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third_party)
add_subdirectory(renderer)
add_subdirectory(application)
