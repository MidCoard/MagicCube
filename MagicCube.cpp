#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"
#include "GLWindows.h"

using  namespace std;

void DRAW();
void Clear();

float vertices[]={

};

unsigned int indices[]={

};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

int main(){
    glfwInit();

    GLWindow untitled_Window;

    Shader untitled_shader("Shaders/vertexShader.vs",
                           "Shaders/fragmentShader.fs");

    DRAW();


    while(!glfwWindowShouldClose(untitled_Window.getWindow())){
        glClearColor(WindowColor[Red],WindowColor[Green],WindowColor[Blue],WindowColor[Alpha]);
        glClear(GL_COLOR_BUFFER_BIT);

        untitled_Window.processInput(untitled_Window.getWindow());

        glBindVertexArray(VAO);




        glfwSwapBuffers(untitled_Window.getWindow());
        glfwPollEvents();
    }

    Clear();
    return 0;
}

void DRAW(){

}

void Clear(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}