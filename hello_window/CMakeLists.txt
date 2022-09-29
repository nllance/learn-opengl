cmake_minimum_required(VERSION 3.10)

project(hello_window)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(hello_window hello_window.cpp ../glad.c)

target_link_libraries(hello_window glfw OpenGL::GL)
