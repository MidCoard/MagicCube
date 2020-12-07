#ifndef UNTITLED_GLWINDOWS_H
#define UNTITLED_GLWINDOWS_H

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

#define ErrorCode -1

const float WindowColor[4]={0.0f,0.0f,0.0f,1.0f};
const unsigned int Red = 0;
const unsigned int Green = 1;
const unsigned int Blue = 2;
const unsigned int Alpha = 3;

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

GLWindow::GLWindow(int Window_Width,int Window_Height, char* Window_Title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(Window_Width, Window_Height, Window_Title, nullptr, nullptr);

    if (window == nullptr)
    {
        cout << "Failed to create GLFW mainWindow" << endl;
        glfwTerminate();
        exit(ErrorCode);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        exit(ErrorCode);
    }
    glViewport(0,0,Window_Width,Window_Height);
}

GLFWwindow* GLWindow::getWindow(){
    return window;
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(window);
}
void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

#endif