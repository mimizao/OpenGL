cmake_minimum_required(VERSION 3.24)
project(03_04_my_shader)

set(CMAKE_CXX_STANDARD 17)

#设置工作目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(03_04_my_shader main.cpp glad.c Shader.h Shader.cpp Shader.h)
target_link_libraries(03_04_my_shader glfw3.lib)