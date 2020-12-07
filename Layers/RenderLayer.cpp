#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "GLWindows.h"
#include "Camera.h"
#include "MagicCube.h"
#include "SetVertices.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "MagicCube"

#define NUM_VERTICES 3
#define NUM_TRIANGLES 36
#define STRIDE(steps) steps * sizeof(float)
#define OFFSET_NULL nullptr
#define OFFSET(steps) (void*)steps

namespace Render {

    using namespace std;
    using namespace glm;
/////////////////////////////////////////////////////////////////////////////////////////

    bool initialize = false;

    bool isInitialize() {
        return initialize;
    }

/////////////////////////////////////////////////////////////////////////////////////////

    GLWindow* mainWindow;

    Shader* cubeShader;

    Camera* camera;

    const vec3 CAMERA_POSITION = vec3(0.0f, 0.0f, 10.0f);

    void draw();

    void render();

    void clear();

    void mouseCallback(GLFWwindow*, double, double);

    void scrollCallback(GLFWwindow*, double, double);

    void resetLocationValue();

    const unsigned int NumBuffers = 1;
    const unsigned int NumVAOs = 1;
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

//////////////////////////////////////////////////////////////////////////////////////////////////
    void initRenderLayer() {
        if(initialize)
            return;

        mainWindow = new GLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        cubeShader = new Shader("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs");
        camera = new Camera(CAMERA_POSITION);

        projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        view = camera->getViewMatrix();

        glfwSetFramebufferSizeCallback(mainWindow->getWindow(), frameBufferSizeCallback);
        glfwSetCursorPosCallback(mainWindow->getWindow(), mouseCallback);
        glfwSetScrollCallback(mainWindow->getWindow(), scrollCallback);

        glEnable(GL_DEPTH_TEST);
        glGenVertexArrays(NumVAOs, MagicCubeVAO);
        glGenBuffers(NumBuffers, MagicCubeVBO);

        setCubeCentralVertices();

        draw();

        initialize = true;
    }

    void draw() {
        glBindVertexArray(MagicCubeVAO[VAOCounter++]);

        glBindBuffer(GL_ARRAY_BUFFER, MagicCubeVBO[BufferCounter++]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(LocationValue, NUM_VERTICES, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
        glEnableVertexAttribArray(LocationValue++);
        glBindBuffer(GL_ARRAY_BUFFER, MagicCubeVBO[BufferCounter++]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]), colors[0], GL_STATIC_DRAW);
//        glVertexAttribPointer(LocationValue, NUM_VERTICES, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
//        glEnableVertexAttribArray(LocationValue++);
        resetLocationValue();
    }

    void render() {
        setMagicCubeVertices();
        view = camera->getViewMatrix();
        projection = perspective(radians(camera->Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        glClearColor(WindowColor[Red], WindowColor[Green], WindowColor[Blue], WindowColor[Alpha]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transpositionLocation = glGetUniformLocation(cubeShader->getProgramId(), "transform");
        glUniformMatrix4fv(transpositionLocation, 1, GL_FALSE, value_ptr(transposition));

        viewLocation = glGetUniformLocation(cubeShader->getProgramId(), "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

        projectionLocation = glGetUniformLocation(cubeShader->getProgramId(), "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

        modelLocation = glGetUniformLocation(cubeShader->getProgramId(), "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

        glBindVertexArray(MagicCubeVAO[0]);
        cubeShader->use();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
            model = mat4(1.0f);
            model = translate(model, cubePositions[i][j][k]);
            modelLocation = glGetUniformLocation(cubeShader->getProgramId(), "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, NUM_TRIANGLES);
                }
            }
        }
        glfwSwapBuffers(mainWindow->getWindow());
        glfwPollEvents();
    }

    void clear() {
        glDeleteVertexArrays(NumVAOs, MagicCubeVAO);
        glDeleteBuffers(NumBuffers, MagicCubeVBO);
        glfwTerminate();
    }

    void resetLocationValue() {
        LocationValue = 0;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

    GLWindow* getWindow() {
        return mainWindow;
    }

    void setFirstMouse(bool flag) {
        firstMouse = flag;
    }
}