cmake_minimum_required(VERSION 3.24)
project(01_hello_window)

set(CMAKE_CXX_STANDARD 11)

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(01_hello_window main.cpp glad.c)
target_link_libraries(01_hello_window glfw3.lib)