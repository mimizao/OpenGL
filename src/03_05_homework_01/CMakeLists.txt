cmake_minimum_required(VERSION 3.24)
project(03_05_homework_01)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(03_05_homework_01 main.cpp glad.c Shader.h Shader.cpp Shader.h)
target_link_libraries(03_05_homework_01 glfw3.lib)