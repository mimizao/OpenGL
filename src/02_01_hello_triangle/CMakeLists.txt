cmake_minimum_required(VERSION 3.24)
project(02_01_hello_triangle)

set(CMAKE_CXX_STANDARD 11)

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(02_01_hello_triangle main.cpp glad.c)
target_link_libraries(02_01_hello_triangle glfw3.lib)