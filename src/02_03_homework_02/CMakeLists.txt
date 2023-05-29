cmake_minimum_required(VERSION 3.24)
project(02_03_homework_02)

set(CMAKE_CXX_STANDARD 11)

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(02_03_homework_02 main.cpp glad.c)
target_link_libraries(02_03_homework_02 glfw3.lib)