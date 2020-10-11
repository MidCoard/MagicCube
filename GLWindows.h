#ifndef UNTITLED_GLWINDOWS_H
#define UNTITLED_GLWINDOWS_H

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define Window_Width 1080
#define Window_Height 1080
#define Window_Title "test"
#define ErrorCode -1

const float WindowColor[4]={0.2f,0.4f,0.6f,1.0f};
const unsigned int Red = 0;
const unsigned int Green = 1;
const unsigned int Blue = 2;
const unsigned int Alpha = 3;

using namespace std;

void frameBufferSizeCallback(GLFWwindow*, int, int);

class GLWindow
{
    private:
        GLFWwindow* window;
    public:
        GLWindow();
        ~GLWindow();

        GLFWwindow* getWindow();
        void processInput(GLFWwindow*);
};

GLWindow::GLWindow() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(Window_Width, Window_Height, Window_Title, nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(ErrorCode);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,frameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        exit(ErrorCode);
    }
    glViewport(0,0,Window_Width,Window_Height);
}
void GLWindow::processInput(GLFWwindow *window0)
{
    if(glfwGetKey(window0, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window0, true);
}
GLFWwindow* GLWindow::getWindow() {
    return window;
}

GLWindow::~GLWindow() {

}

void frameBufferSizeCallback(GLFWwindow* window0, int width, int height){
    glViewport(0, 0, width, height);
}

#endif