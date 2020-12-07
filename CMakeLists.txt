cmake_minimum_required(VERSION 3.17)
project(MagicCube)

set(CMAKE_CXX_STANDARD 14)

## 检查环境变量
#if (NOT DEFINED ENV{GLFW_HOME})
#    message(FATAL_ERROR "found no env named GLFW_HOME")
#endif ()
#if (NOT DEFINED ENV{GLAD_HOME})
#    message(FATAL_ERROR "found no env named GLAD_HOME")
#endif ()
## 暂存环境变量
#set(GLFW_HOME $ENV{GLFW_HOME})
#set(GLAD_HOME $ENV{GLAD_HOME})
#
## 设置头文件目录
#include_directories("${GLFW_HOME}/include/")
#include_directories("${GLAD_HOME}/include/")
include_directories(include)
include_directories(HeaderFiles)
include_directories(${PROJECT_SOURCE_DIR})
#add_library(glfw SHARED IMPORTED)
add_executable(MagicCube glad.c MagicCubeLauncher.cpp HeaderFiles/SetVertices.h)
if (APPLE)
    #    set(GLEW_LINK ${PROJECT_SOURCE_DIR}/lib/libGLEW.2.1.dylib)
    set(GLFW_LINK ${PROJECT_SOURCE_DIR}/lib/libglfw.3.dylib)
    target_link_libraries(MagicCube ${GLFW_LINK})
    target_link_libraries(MagicCube "-framework OpenGL")
    target_link_libraries(MagicCube "-framework GLUT")
else ()
    target_link_libraries(MagicCube ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
endif ()