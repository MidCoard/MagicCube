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
#include "RenderPoint.h"
#include "MagicCube.h"
#include "util.cpp"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "MagicCube"
#define WINDOW_SHOULD_NOT_CLOSE !glfwWindowShouldClose(MainWindow.getWindow())

namespace Render {


    using namespace std;
    using namespace glm;

    GLWindow MainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    Shader MagicCubeShader("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs");

    Camera Camera(vec3(0.0f, 0.0f, 6.0f));

    void init();

    void draw();

    void render();

    void clear();

    void processInput();

    void mouseCallback(GLFWwindow *window, double xCoordinate, double yCoordinate);

    void scrollCallback(GLFWwindow *, double, double);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const unsigned int NumBuffers = 2;
    const unsigned int NumVAOs = 2;
    unsigned int LocationValue = 0;

    mat4 transposition = mat4(1.0f);
    mat4 projection = mat4(1.0f);
    mat4 model = mat4(1.0f);
    mat4 view = mat4(1.0f);

    unsigned int transpositionLocation;
    unsigned int modelLocation;
    unsigned int viewLocation;
    unsigned int projectionLocation;

    void init() {
        projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        transposition = rotate(transposition, radians(90.0f), vec3(0.0, 0.0, 0.0));
        view = Camera.GetViewMatrix();

        glfwSetFramebufferSizeCallback(MainWindow.getWindow(), frameBufferSizeCallback);
        glfwSetCursorPosCallback(MainWindow.getWindow(), mouseCallback);
        glfwSetScrollCallback(MainWindow.getWindow(), scrollCallback);
    }

    unsigned int VAO[NumVAOs];
    unsigned int VBO[NumBuffers];

    float vertices1[] = {
            -1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
    };
    float vertices2[] = {
            0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    void draw() {
        glGenVertexArrays(NumVAOs, VAO);
        glGenBuffers(NumBuffers, VBO);

        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 3);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 3);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glEnable(GL_DEPTH_TEST);
    }

    void render() {
        view = Camera.GetViewMatrix();
        projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        glClearColor(WindowColor[Red], WindowColor[Green], WindowColor[Blue], WindowColor[Alpha]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transpositionLocation = glGetUniformLocation(MagicCubeShader.getProgramId(), "transform");
        glUniformMatrix4fv(transpositionLocation, 1, GL_FALSE, value_ptr(transposition));

        viewLocation = glGetUniformLocation(MagicCubeShader.getProgramId(), "view");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

        projectionLocation = glGetUniformLocation(MagicCubeShader.getProgramId(), "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));

        modelLocation = glGetUniformLocation(MagicCubeShader.getProgramId(), "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

        MagicCubeShader.use();
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

//    MagicCubeShader1.use();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void clear() {
        glDeleteVertexArrays(NumVAOs, VAO);
        glDeleteBuffers(NumBuffers, VBO);
        glfwTerminate();
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float lastX = WINDOW_WIDTH / 2.0f;
    float lastY = WINDOW_HEIGHT / 2.0f;
    bool firstMouse = true;

    void processInput() {
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(MainWindow.getWindow(), true);
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            Camera.ProcessKeyboard(CAMERAFORWARD, deltaTime);
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            Camera.ProcessKeyboard(CAMERABACKWARD, deltaTime);
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            Camera.ProcessKeyboard(CAMERALEFT, deltaTime);
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            Camera.ProcessKeyboard(CAMERARIGHT, deltaTime);
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
            glfwSetInputMode(MainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstMouse = true;
        }
        if (glfwGetKey(MainWindow.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
            glfwSetInputMode(MainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

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

        Camera.ProcessMouseMovement(xOffset, yOffset);
    }

    void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
        Camera.ProcessMouseScroll(yOffset);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void initRenderLayer() {
        magicCube.getBlock(0,0,0)->
        init();
        draw();
        while (WINDOW_SHOULD_NOT_CLOSE) {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            processInput();
            render();
            glfwSwapBuffers(MainWindow.getWindow());
            glfwPollEvents();
        }
        clear();
//        return 0;
    }
}