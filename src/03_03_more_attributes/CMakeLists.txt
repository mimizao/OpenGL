cmake_minimum_required(VERSION 3.24)
project(03_03_more_attributes)

set(CMAKE_CXX_STANDARD 11)

#头文件
include_directories(..\\..\\include)

#库
link_directories(..\\..\\libs)
link_libraries(glfw3.lib)

add_executable(03_03_more_attributes main.cpp glad.c)
target_link_libraries(03_03_more_attributes glfw3.lib)