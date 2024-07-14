cmake_minimum_required(VERSION 3.26)
project(OpenGLTest)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(glad REQUIRED)
add_executable(OpenGLTest main.cpp glad.c)

# Include directory containing glad.h
#target_include_directories(OpenGLTest PRIVATE "C:\\msys64\\ucrt64\\include\\glad")

# Link OpenGL and glad libraries
target_link_libraries(OpenGLTest PRIVATE ${OPENGL_LIBRARIES} glfw)