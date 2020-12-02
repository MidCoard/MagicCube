#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "GLWindows.h"
#include "Camera.h"
#include "MagicCube.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "MagicCube"
#define WINDOW_SHOULD_NOT_CLOSE !glfwWindowShouldClose(MainWindow.getWindow())

#define NUM_VERTICES 3
#define STRIDE(steps) steps * sizeof(float)
#define OFFSET_NULL nullptr
#define OFFSET(steps) (void*)steps

namespace Render {

    bool initialize = false;

    bool isInitialize() {
        return initialize;
    }

    using namespace std;
    using namespace glm;

    GLWindow*window;

    Shader*shader;

    Camera* camera;

    void init();

    void draw();

    void render();

    void clear();

    void processInput();

    void mouseCallback(GLFWwindow *window, double xCoordinate, double yCoordinate);

    void scrollCallback(GLFWwindow *, double, double);

    void resetLocationValue();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const unsigned int NumBuffers = 4;
    const unsigned int NumVAOs = 2;
    unsigned int LocationValue = 0;
    unsigned int BufferCounter = 0;
    unsigned int VAOCounter = 0;

    mat4 transposition = mat4(1.0f);
    mat4 projection = mat4(1.0f);
    mat4 model = mat4(1.0f);
    mat4 view = mat4(1.0f);

    unsigned int transpositionLocation;
    unsigned int modelLocation;
    unsigned int viewLocation;
    unsigned int projectionLocation;

    unsigned int MagicCubeVAO[NumVAOs];
    unsigned int MagicCubeVBO[NumBuffers];

    float vertices[2][9] = {
            {-1.0f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f},

            {0.0f, -0.5f, 0.0f,
            1.0f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f}
    };
    float colors[2][9]={
            {1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f}
    };
    void draw() {
        glGenVertexArrays(NumVAOs, MagicCubeVAO);
        glGenBuffers(NumBuffers, MagicCubeVBO);
        for(int i=0;i<NumVAOs-1;i++) {
            glBindVertexArray(MagicCubeVAO[VAOCounter]);

            glBindBuffer(GL_ARRAY_BUFFER, MagicCubeVBO[BufferCounter]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
            glVertexAttribPointer(LocationValue, NUM_VERTICES, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
            glEnableVertexAttribArray(LocationValue++);
            BufferCounter++;
            glBindBuffer(GL_ARRAY_BUFFER, MagicCubeVBO[BufferCounter]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(colors[i]), colors[i], GL_STATIC_DRAW);
            glVertexAttribPointer(LocationValue, NUM_VERTICES, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
            glEnableVertexAttribArray(LocationValue++);
            resetLocationValue();
            BufferCounter++;
            VAOCounter++;
        }
        //todo
        glEnable(GL_DEPTH_TEST);
    }

    void render() {
        view = camera->getViewMatrix();
        projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        glClearColor(WindowColor[Red], WindowColor[Green], WindowColor[Blue], WindowColor[Alpha]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transpositionLocation = glGetUniformLocation(shader->getProgramId(), "transform");
        glUniformMatrix4fv(transpositionLocation, 1, GL_FALSE, value_ptr(transposition));

        viewLocation = glGetUniformLocation(shader->getProgramId(), "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

        projectionLocation = glGetUniformLocation(shader->getProgramId(), "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

        modelLocation = glGetUniformLocation(shader->getProgramId(), "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

        shader->use();
        for(int i=0;i<NumVAOs-1;i++) {
            glBindVertexArray(MagicCubeVAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        glfwSwapBuffers(window->getWindow());
        glfwPollEvents();
    }

    void clear() {
        glDeleteVertexArrays(NumVAOs, MagicCubeVAO);
        glDeleteBuffers(NumBuffers, MagicCubeVBO);
        glfwTerminate();
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastX = WINDOW_WIDTH / 2.0f;
    float lastY = WINDOW_HEIGHT / 2.0f;
    bool firstMouse = true;



    void mouseCallback(GLFWwindow *window, double xCoordinate, double yCoordinate) {
        if (firstMouse) {
            lastX = xCoordinate;
            lastY = yCoordinate;
            firstMouse = false;
        }

        float xOffset = xCoordinate - lastX;
        float yOffset = lastY - yCoordinate;

        lastX = xCoordinate;
        lastY = yCoordinate;

        camera->processMouseMovement(xOffset, yOffset);
    }

    void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
        camera->ProcessMouseScroll(yOffset);
    }

    Camera* getCamera(){
        return camera;
    }

    GLWindow* getWindow() {
        return window;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void initRenderLayer() {
//        magicCube.getBlock(0,0,0)->
//        magicCube.getBlock(0,0,0)->getRenderBlock().getTriangle(1).get(0).getX();
        if(initialize)
            return;
        window = new GLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        shader = new Shader("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs");
        camera = new Camera(vec3(0.0f, 0.0f, 6.0f));
        projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        transposition = rotate(transposition, radians(90.0f), vec3(0.0, 0.0, 0.0));
        view = camera->getViewMatrix();

        glfwSetFramebufferSizeCallback(window->getWindow(), frameBufferSizeCallback);
        glfwSetCursorPosCallback(window->getWindow(), mouseCallback);
        glfwSetScrollCallback(window->getWindow(), scrollCallback);
        draw();

        //todo clear
        initialize = true;
    }

    void resetLocationValue() {
        LocationValue = 0;
    }

    void setFirstMouse(bool flag) {
        firstMouse = flag;
    }
}