cmake_minimum_required(VERSION 3.17)
project(MagicCube)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES MagicCubeLauncher.cpp)

include_directories(include)
include_directories(utils)
include_directories(layers)
#include_directories(${PROJECT_SOURCE_DIR})
#add_library(glfw SHARED IMPORTED)
add_executable(MagicCube ${SOURCE_FILES} glad.c include/stb_image.cpp utils/Configuration.cpp utils/util.cpp utils/Shader.cpp utils/Matrix.cpp utils/Image.cpp utils/GLWindow.cpp utils/ColorState.cpp utils/Color.cpp utils/Camera.cpp layers/LogicLayer.cpp layers/RenderLayer.cpp)
target_link_libraries(MagicCube ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")