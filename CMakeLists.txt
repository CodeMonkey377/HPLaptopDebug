cmake_minimum_required(VERSION 3.26)
project(OpenGLTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(glad/include)
include_directories(glfw-3.4/include)
add_library(glad STATIC glad/src/glad.c)

set(GLFW_BUILD_WAYLAND OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(glfw-3.4)

add_executable(OpenGLTest main.cpp glad/src/glad.c)

# Include directory containing glad.h
#target_include_directories(OpenGLTest PRIVATE "C:\\msys64\\ucrt64\\include\\glad")

# Link OpenGL and glad libraries
target_link_libraries(OpenGLTest glad glfw ${GLFW_LIBRARIES})