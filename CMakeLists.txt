cmake_minimum_required(VERSION 3.10)

project(out)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(out modelling.cpp)
target_link_libraries(out OpenGL::GL)
target_link_libraries(out glfw)
