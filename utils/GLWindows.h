#ifndef MAGICCUBE_GLWINDOWS_H
#define MAGICCUBE_GLWINDOWS_H

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

#define ErrorCode -1

mat4 transformMatrix = mat4(1.0f);

const ColorRGBA WINDOW_COLOR = ColorRGBA(0.2f, 0.4f, 0.6f, 1.0f);

using namespace std;

class GLWindow
{
    private:
        GLFWwindow* window;
    public:
        GLWindow(int,int,char*);
        ~GLWindow();

        GLFWwindow* getWindow();
};

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

#endif