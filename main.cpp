#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "HeaderFiles/Shader.h"
#include "HeaderFiles/GLWindows.h"
#include "HeaderFiles/Camera.h"
#include "HeaderFiles/RenderPoint.h"
#include "HeaderFiles/MagicCube.h"

#define Window_Width 1080
#define Window_Height 1080
#define Window_Title "MagicCube"
#define WindowShouldNotClose !glfwWindowShouldClose(MainWindow.getWindow())

using namespace std;
using namespace glm;

void Draw();
void Render();
void Clear();
void processInput();

float lastX = Window_Width / 2.0f;
float lastY = Window_Height / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLWindow MainWindow(Window_Width,Window_Height,Window_Title);

Shader MagicCubeShader("Shaders/vertexShader.vs","Shaders/fragmentShader.fs");

Camera Camera(vec3(0.0f, 0.0f, 6.0f));

using namespace std;

unsigned int VBO1,VAO1;
unsigned int VBO2,VAO2;

float vertices1[]={
        -1.0f,-0.5f,0.0f,1.0f,0.0f,0.0f,
        0.0f,-0.5f,0.0f,1.0f,0.0f,0.0f,
        -0.5f,0.5f,0.0f,1.0f,0.0f,0.0f
};
float vertices2[]={
        0.0f,-0.5f,0.0f,0.0f,0.0f,1.0f,
        1.0f,-0.5f,0.0f,0.0f,0.0f,1.0f,
        0.5f,0.5f,0.0f,0.0f,0.0f,1.0f
};

int main(){

    Draw();
    while(WindowShouldNotClose){
        Render();
    }

    Clear();
    return 0;
}

void Draw(){
    glGenBuffers(1,&VBO1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)3);
    glEnableVertexAttribArray(1);
}
void Render(){
    glClearColor(WindowColor[Red],WindowColor[Green],WindowColor[Blue],WindowColor[Alpha]);
    glClear(GL_COLOR_BUFFER_BIT);

    processInput();

    glBindVertexArray(VAO1);


    glfwSwapBuffers(MainWindow.getWindow());
    glfwPollEvents();
}
void Clear(){
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glfwTerminate();
}
void processInput()
{
    if(glfwGetKey(MainWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(MainWindow.getWindow(), true);
    if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        Camera.ProcessKeyboard(CAMERAFORWARD, deltaTime);
    if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        Camera.ProcessKeyboard(CAMERABACKWARD, deltaTime);
    if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        Camera.ProcessKeyboard(CAMERALEFT, deltaTime);
    if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        Camera.ProcessKeyboard(CAMERARIGHT, deltaTime);
    if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
        glfwSetInputMode(MainWindow.getWindow(),GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse=true;
    }
    if(glfwGetKey(MainWindow.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
        glfwSetInputMode(MainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}