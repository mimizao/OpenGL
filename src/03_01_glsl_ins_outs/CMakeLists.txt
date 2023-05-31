cmake_minimum_required(VERSION 3.24)
project(03_01_glsl_ins_outs)

set(CMAKE_CXX_STANDARD 11)

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(03_01_glsl_ins_outs main.cpp glad.c)
target_link_libraries(03_01_glsl_ins_outs glfw3.lib)