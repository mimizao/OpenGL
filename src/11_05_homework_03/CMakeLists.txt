cmake_minimum_required(VERSION 3.24)
project(11_05_homework_03)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

#头文件
include_directories(..\\..\\include "${CMAKE_CURRENT_SOURCE_DIR}/include")

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(11_05_homework_03 main.cpp glad.c src/Shader.cpp src/Camera.cpp)
target_link_libraries(11_05_homework_03 glfw3.lib)