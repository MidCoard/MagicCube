#include <iostream>

#include"glad/glad.h"
#include "GLFW/glfw3.h"

#define Window_Width 1920
#define Window_Height 1080
#define Window_Title "MagicCube"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

using  namespace std;

GLFWwindow *window;
const float WindowColor[5]={0.0f,0.2f, 0.3f, 0.3f, 1.0f};

void processInput(GLFWwindow*);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void initWindow();
void initShaderProgram();
void DRAW();
void Clear();

float vertices[]={

};

unsigned int VBO;
unsigned int VAO;

unsigned int vertexShader;
unsigned int fragmentShader;

int shaderProgram;

int  vertexShader_success;
int  fragmentShader_success;
int  programLinking_success;
char vertexShader_infoLog[512];
char fragmentShader_infoLog[512];
char programLinking_infoLog[512];

int main(){
    glfwInit();
    initWindow();
    initShaderProgram();
    DRAW();

    while(!glfwWindowShouldClose(window)){
        glClearColor(WindowColor[1],WindowColor[2],WindowColor[3],WindowColor[4]);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
        processInput(window);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Clear();
    return 0;
}
void initWindow(){
    window = glfwCreateWindow(Window_Width, Window_Height, Window_Title, nullptr, nullptr);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        exit(-1);
    }
    glViewport(0,0,Window_Width,Window_Height);
}

void initShaderProgram(){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    shaderProgram=glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShader_success);
    if(!vertexShader_success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShader_infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertexShader_infoLog << endl;
        exit(-1);
    }                                                                                   //顶点着色器编译

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShader_success);
    if (!fragmentShader_success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentShader_infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentShader_infoLog << std::endl;
        exit(-1);
    }                                                                               //片段着色器编译

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programLinking_success);
    if(!programLinking_success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, programLinking_infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << programLinking_infoLog << endl;
        exit(-1);
    }
}

void DRAW(){

}

void Clear(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}