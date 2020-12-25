#ifndef MAGICCUBE_GLWINDOWS_H
#define MAGICCUBE_GLWINDOWS_H

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

#define ErrorCode -1
extern mat4 transformMatrix;

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