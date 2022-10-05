cmake_minimum_required(VERSION 3.10)

project(hello_triangle)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(hello_triangle hello_triangle.cpp ../glad.c)

target_link_libraries(hello_triangle glfw OpenGL::GL)
