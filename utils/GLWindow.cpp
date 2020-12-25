#include "GLWindows.h"


mat4 transformMatrix = mat4(1.0f);

GLWindow::GLWindow(int windowWidth,int windowHeight, char* windowTitle) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

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
    glViewport(0,0,windowWidth,windowHeight);
}

GLFWwindow* GLWindow::getWindow(){
    return window;
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(window);
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    transformMatrix = mat4(1.0f);
    if (height>width)
    	transformMatrix = scale(transformMatrix, vec3((float)width / (float)height, 1.0f, (float)width / (float)height));
    else transformMatrix = scale(transformMatrix, vec3((float)height / (float)width, 1.0f, (float)height / (float)width));
}
