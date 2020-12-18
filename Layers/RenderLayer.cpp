#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mutex>

#include "Shader.h"
#include "GLWindows.h"
#include "Camera.h"
#include "SetVertices.h"
#include "Text.h"
#include "RenderLayer.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "MagicCube"

#define NUM_READIN 3
#define STRIDE(steps) steps * sizeof(float)
#define OFFSET_NULL nullptr
#define NO_JUMP 0
#define OFFSET(steps) (void*)steps  //使代码可读性增强

using namespace std;
using namespace glm;

enum STATE {
    STOP,
    ROTATE_X,
    ROTATE_Y,
    ROTATE_Z,
    UPDATE
} cubeState = STOP;//记录旋转信息

enum ROTATE_FLAG {
    NO_ROTATE,
    ROTATE_X_1,
    ROTATE_X_2,
    ROTATE_X_3,
    ROTATE_Y_1,
    ROTATE_Y_2,
    ROTATE_Y_3,
    ROTATE_Z_1,
    ROTATE_Z_2,
    ROTATE_Z_3
} rotateFlag = NO_ROTATE;//标记要旋转的层数

#define X_1 x > -(2*CUBE_LENGTH+GAP)-0.01f && x < -(2*CUBE_LENGTH+GAP)+0.01f
#define X_2 x > -0.01f && x < 0.01f
#define X_3 x > (2*CUBE_LENGTH+GAP)-0.01f && x < (2*CUBE_LENGTH+GAP)+0.01f

#define Y_1 y > (2*CUBE_LENGTH+GAP)-0.01f && y < (2*CUBE_LENGTH+GAP)+0.01f
#define Y_2 y > -0.01f && y < 0.01f
#define Y_3 y > -(2*CUBE_LENGTH+GAP)-0.01f && y < -(2*CUBE_LENGTH+GAP)+0.01f

#define Z_1 z > (2*CUBE_LENGTH+GAP)-0.01f && z < (2*CUBE_LENGTH+GAP)+0.01f
#define Z_2 z > -0.01f && z < 0.01f
#define Z_3 z > -(2*CUBE_LENGTH+GAP)-0.01f && z < -(2*CUBE_LENGTH+GAP)+0.01f //规定每层的坐标，这里取一个小区间避免定位失败

bool StartGameLoop = false;
bool ifPause = false;
bool ifHelp = false;

bool isStartGameLoop() {
    return StartGameLoop;
}

namespace Render {

/////////////////////////////////////////////////////////////////////////////////////////

    bool initialize = false;

    bool isInitialize() {
        return initialize;
    }

/////////////////////////////////////////////////////////////////////////////////////////

    GLWindow *mainWindow;

    Shader *cubeShader;

    Camera *camera;

    void StartMenu();

    void attribPointer();

    void setCubeMatrix();

    void GameLoop(double);

    void clear();

    void mouseCallback(GLFWwindow *, double, double);

    void scrollCallback(GLFWwindow *, double, double);

    unsigned int LocationValue = 0;

    mat4 projection = mat4(1.0f);
    mat4 view = mat4(1.0f);

    mat4 currentModel = mat4(1.0f);
    vector<mat4> allCubesState(NUM_CUBES, mat4(1.0f));
    const mat4 identityMatrix = mat4(1.0f);//单位矩阵

    const double rotateVelocity = 4.0;
    float angle = 0.0;
    float targetAngle = 90.0;
    vec3 rotationVector;
    mutex cubeMutex;

    GLuint MagicCubeVAO,MagicCubeVBO;
    GLuint ColorVBO;
//////////////////////////////////////////////////////////////////////////////////////light

    Shader *lightShader;
    GLuint lightVAO,lightVBO;
    GLuint normalVBO;
    vec3 lightPosition = CAMERA_POSITION;
    mat4 lightModel = mat4(1.0f);
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

//////////////////////////////////////////////////////////////////////////////////////////////////

    mat4 * getCubeState(int x,int y,int z) {
        return &allCubesState[x*9  + y * 3  + z ];
    }

    void resetStates() {
        for(int i=0;i<NUM_CUBES;i++){
            Render::allCubesState[i] = mat4(1.0f);
        }
    }


    void initRenderLayer(char* state) {
        if (initialize)
            return;

        mainWindow = new GLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        cubeShader = new Shader("Shaders/MagicCube.vs", "Shaders/MagicCube.fs");
        lightShader = new Shader("Shaders/Light.vs", "Shaders/Light.fs");
        camera = new Camera(CAMERA_POSITION);

        projection = perspective(radians(ZOOM), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        view = camera->getViewMatrix();

        setWorldSpace();
        setColors(logicColors[0],logicColors[1],logicColors[2],logicColors[3],logicColors[4],logicColors[5]);

        glfwSetFramebufferSizeCallback(mainWindow->getWindow(), frameBufferSizeCallback);
        glfwSetCursorPosCallback(mainWindow->getWindow(), mouseCallback);
        glfwSetScrollCallback(mainWindow->getWindow(), scrollCallback);

        initText();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGenVertexArrays(1, &MagicCubeVAO);

        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1,&lightVBO);

        attribPointer();

        lightModel = translate(lightModel, lightPosition);
        lightModel = scale(lightModel, vec3(0.2f));
        string check(state);
        if (!check.empty()) {
            FILE *file = fopen(state, "rb");
            if (file == NULL) {
                cout<<"Cannot open "<<state<<endl;
                cout<<"Use default states"<<endl;
            } else {
                cout<<"Find valid states"<<endl;
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        for (int k = 0; k < 3; k++)
                            fread(Render::getCubeState(i, j, k), sizeof(mat4), 1, file);
                fclose(file);
            }
        }
        initialize = true;
    }

    void StartMenu(){
        projection = perspective(radians(camera->Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        view = lookAt(vec3(0.0f,0.0f,10.0f), vec3(0, 0, 0), camera->WorldUp);
        glClearColor(WindowColor[R], WindowColor[G], WindowColor[B], WindowColor[A]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float alpha = abs(sin(glfwGetTime()));
        renderText(vec3(0,2,0),3.3f,1.1f,1.0f,view,projection,(char*)"C:/Users/Ken/DeskTop/images/Title.png");
        renderText(vec3(0,0.2,0),2.79f,0.93f,alpha,view,projection,(char*)"C:/Users/Ken/DeskTop/images/Start.png");
        renderText(vec3(0,-2,0),1.8f,0.6f,1.0f,view,projection,(char*)"C:/Users/Ken/DeskTop/images/Help.png");
        glfwSwapBuffers(mainWindow->getWindow());
        glfwPollEvents();
    };

    void Pause(){
        projection = perspective(radians(camera->Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        view = lookAt(vec3(0.0f,0.0f,10.0f), vec3(0, 0, 0), camera->WorldUp);
        glClearColor(WindowColor[R], WindowColor[G], WindowColor[B], WindowColor[A]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderText(vec3(0,0.5,0),3.0f,1.0f,1.0f,view,projection,(char*)"C:/Users/Ken/DeskTop/images/Pause.png");
        renderText(vec3(0,-1,0),2.4f,0.8f,1.0f,view,projection,(char*)"C:/Users/Ken/DeskTop/images/Help.png");
        glfwSwapBuffers(mainWindow->getWindow());
        glfwPollEvents();
    }

    void Help(){
        projection = perspective(radians(camera->Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        view = lookAt(vec3(0.0f,0.0f,10.0f), vec3(0, 0, 0), camera->WorldUp);
        glClearColor(WindowColor[R], WindowColor[G], WindowColor[B], WindowColor[A]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderText(vec3(0,0,0),4.2f,4.2f,1.0f,view,projection,(char*)"C:/Users/Ken/DeskTop/images/HelpContent.png");
        glfwSwapBuffers(mainWindow->getWindow());
        glfwPollEvents();
    }

    void attribPointer() {
        glBindVertexArray(MagicCubeVAO);

        glGenBuffers(1, &MagicCubeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, MagicCubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(localCubeVertices), localCubeVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(LocationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
        glEnableVertexAttribArray(LocationValue++);//链接顶点

        glGenBuffers(1, &normalVBO);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(normalVector), normalVector, GL_STATIC_DRAW);
        glVertexAttribPointer(LocationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
        glEnableVertexAttribArray(LocationValue++);//链接法向量

        glGenBuffers(1, &ColorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, ColorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
        glVertexAttribPointer(LocationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
        glEnableVertexAttribArray(LocationValue++);//链接颜色

        LocationValue = 0;

        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(localCubeVertices), localCubeVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(LocationValue, NUM_READIN, GL_FLOAT, GL_FALSE, STRIDE(3), OFFSET_NULL);
        glEnableVertexAttribArray(LocationValue++);//链接光源顶点
    }

    void setCubeMatrix() {
        view = camera->getViewMatrix();

        projection = perspective(radians(camera->Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        cubeShader->setMat4("transform", transformMatrix);

        cubeShader->setMat4("view", view);

        cubeShader->setMat4("projection", projection);

        cubeShader->setVec3("lightColor", lightColor);

        cubeShader->setVec3("lightPos",lightPosition);

        cubeShader->setVec3("viewPos",camera->Position);
    }

    void setLightMatrix(){
        view = camera->getViewMatrix();

        lightShader->setMat4("transform", transformMatrix);

        lightShader->setMat4("lightModel",lightModel);

        lightShader->setMat4("view", view);

        lightShader->setMat4("projection", projection);

        lightShader->setVec3("lightColor", lightColor);

        lightShader->setVec3("lightPos",lightPosition);
    }

    bool ignoreKeyboardInput = false;

    bool isIgnoreKeyboardInput() {
        return ignoreKeyboardInput;
    }

    void GameLoop(double elapsed) {
        lightPosition = camera->Position;
        projection = perspective(radians(camera->Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        view = camera->getViewMatrix();

        glClearColor(WindowColor[R], WindowColor[G], WindowColor[B], WindowColor[A]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        lightShader->use();
//        setLightMatrix();
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_TRIANGLES);//绘制光源

        cubeShader->use();
        setCubeMatrix();
        glBindVertexArray(MagicCubeVAO);
        mat4 model = mat4(1.0f);
        switch (cubeState) {
            case STOP: {
                for (int i = 0; i < NUM_CUBES; i++) {
                    mat4 templeCurrentModel = currentModel;
                    templeCurrentModel *= allCubesState[i];
                    model = translate(templeCurrentModel, cubePositions[i]);
                    cubeShader->setMat4("model", model);
                    setCubeMatrix();
                    glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
                }
                if (rotateFlag == ROTATE_X_1 || rotateFlag == ROTATE_X_2 || rotateFlag == ROTATE_X_3) {
                    cubeState = ROTATE_X;
                    angle = 0.0;
                    rotationVector = standardXAxis;
                } else if (rotateFlag == ROTATE_Y_1 || rotateFlag == ROTATE_Y_2 || rotateFlag == ROTATE_Y_3) {
                    cubeState = ROTATE_Y;
                    angle = 0.0;
                    rotationVector = standardYAxis;
                } else if (rotateFlag == ROTATE_Z_1 || rotateFlag == ROTATE_Z_2 || rotateFlag == ROTATE_Z_3) {
                    cubeState = ROTATE_Z;
                    angle = 0.0;
                    rotationVector = standardZAxis;
                }
                break;
            }
            case ROTATE_X: {
                angle += rotateVelocity * elapsed * targetAngle;
                for (int i = 0; i < NUM_CUBES; i++) {
                    mat3 allMatsM3 = allCubesState[i];
                    vec3 newCube = allMatsM3 * cubePositions[i];
                    float &x = newCube.x;
                    if (rotateFlag == ROTATE_X_1) {
                        if (X_1) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    } else if (rotateFlag == ROTATE_X_2) {
                        if (X_2) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    } else if (rotateFlag == ROTATE_X_3) {
                        if (X_3) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    }
                    cubeShader->setMat4("model", model);
                    glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);

                }
                if ((targetAngle > 0 && angle >= targetAngle) || (targetAngle < 0 && angle <= targetAngle)) {
                    cubeState = UPDATE;
                } else {
                    ignoreKeyboardInput = true;
                }
                break;
            }
            case ROTATE_Y: {
                angle += rotateVelocity * elapsed * targetAngle;
                for (int i = 0; i < NUM_CUBES; i++) {
                    mat3 allMatsM3 = allCubesState[i];
                    vec3 newCube = allMatsM3 * cubePositions[i];
                    float &y = newCube.y;
                    if (rotateFlag == ROTATE_Y_1) {
                        if (Y_1) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    } else if (rotateFlag == ROTATE_Y_2) {
                        if (Y_2) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    } else if (rotateFlag == ROTATE_Y_3) {
                        if (Y_3) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    }
                    cubeShader->setMat4("model", model);
                    glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
                }
                if ((targetAngle > 0 && angle >= targetAngle) || (targetAngle < 0 && angle <= targetAngle)) {
                    cubeState = UPDATE;
                } else {
                    ignoreKeyboardInput = true;
                }
                break;
            }
            case ROTATE_Z: {
                angle += rotateVelocity * elapsed * targetAngle;
                for (int i = 0; i < NUM_CUBES; i++) {
                    mat3 allMatsM3 = allCubesState[i];
                    vec3 newCube = allMatsM3 * cubePositions[i];
                    float &z = newCube.z;
                    if (rotateFlag == ROTATE_Z_1) {
                        if (Z_1) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    } else if (rotateFlag == ROTATE_Z_2) {
                        if (Z_2) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    } else if (rotateFlag == ROTATE_Z_3) {
                        if (Z_3) {
                            mat4 templeCurrentModel = rotate(currentModel, radians(angle), rotationVector);
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        } else {
                            mat4 templeCurrentModel = currentModel;
                            templeCurrentModel *= allCubesState[i];
                            model = translate(templeCurrentModel, cubePositions[i]);
                        }
                    }
                    cubeShader->setMat4("model", model);
                    glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
                }
                if ((targetAngle > 0 && angle >= targetAngle) || (targetAngle < 0 && angle <= targetAngle)) {
                    cubeState = UPDATE;
                } else {
                    ignoreKeyboardInput = true;
                }
                break;
            }
            case UPDATE: {
                unique_lock<mutex> lock(cubeMutex);
                ignoreKeyboardInput = false;
                for (int i = 0; i < NUM_CUBES; i++) {
                    mat3 allMatsM3 = allCubesState[i];
                    vec3 newCube = allMatsM3 * cubePositions[i];
                    float &x = newCube.x;
                    float &y = newCube.y;
                    float &z = newCube.z;
                    if (rotateFlag == ROTATE_X_1) {
                        if (X_1) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardXAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
//                            mat4 transyaxis = rotate(mat4(1.0f),radians(-targetAngle),standardXAxis);
//                            yaxis[i] = vec3(transyaxis * vec4(yaxis[i],1.0f));
                        }
                    } else if (rotateFlag == ROTATE_X_2) {
                        if (X_2) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardXAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_X_3) {
                        if (X_3) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardXAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_Y_1) {
                        if (Y_1) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardYAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_Y_2) {
                        if (Y_2) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardYAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_Y_3) {
                        if (Y_3) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardYAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_Z_1) {
                        if (Z_1) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardZAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_Z_2) {
                        if (Z_2) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardZAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    } else if (rotateFlag == ROTATE_Z_3) {
                        if (Z_3) {
                            mat4 thisTime = rotate(identityMatrix, radians(targetAngle), standardZAxis);
                            allCubesState[i] = thisTime * allCubesState[i];
                        }
                    }
                }
                lock.unlock();
                for (int i = 0; i < NUM_CUBES; i++) {
                    mat4 templeCurrentModel = currentModel;
                    templeCurrentModel *= allCubesState[i];
                    model = translate(templeCurrentModel, cubePositions[i]);
                    cubeShader->setMat4("model", model);
                    glDrawArrays(GL_TRIANGLES, NO_JUMP, NUM_VERTICES);
                }
                cubeState = STOP;
                targetAngle = 0;
                rotateFlag = NO_ROTATE;
#ifdef DEBUG
                system("cls");
                for (int i = 0;i<27;i++) {
                    for (int j = 0; j < 4; j++) {
                        for (int k = 0; k < 4; k++)
                            printf("%d ",(int)round(allCubesState[i][j][k]));
                        cout<<endl;
                    }
                    cout<< "%%%%%%%%%"<<endl;
                }
#endif
                if (Logic::isSolved() && !Logic::isInShuffling()) {
                    cout<<"Solved it!"<<endl;
                }
                break;
            }
        }
        glfwSwapBuffers(mainWindow->getWindow());
        glfwPollEvents();
    }

    void clear() {
        glDeleteVertexArrays(1, &MagicCubeVAO);
        glDeleteBuffers(1, &MagicCubeVBO);
        glDeleteBuffers(1,&ColorVBO);
        glDeleteVertexArrays(1,&lightVAO);
        glDeleteBuffers(1,&lightVBO);
        glDeleteVertexArrays(1,&textVAO);
        glDeleteBuffers(1,&textVBO);
        glfwTerminate();
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    float lastX = WINDOW_WIDTH / 2.0f;
    float lastY = WINDOW_HEIGHT / 2.0f;
    bool firstMouse = true;

    void mouseCallback(GLFWwindow *window, double xCoordinate, double yCoordinate) {
        if(ifPause || ifHelp) return;
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

    GLWindow *getWindow() {
        return mainWindow;
    }

    void setFirstMouse(bool flag) {
        firstMouse = flag;
    }

    void rotate_X_1(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_X_1;
        targetAngle = degrees;
    }

    void rotate_X_2(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_X_2;
        targetAngle = degrees;
    }

    void rotate_X_3(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_X_3;
        targetAngle = degrees;
    }

    void rotate_Y_1(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_Y_1;
        targetAngle = degrees;
    }

    void rotate_Y_2(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_Y_2;
        targetAngle = degrees;
    }

    void rotate_Y_3(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_Y_3;
        targetAngle = degrees;
    }

    void rotate_Z_1(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_Z_1;
        targetAngle = degrees;
    }

    void rotate_Z_2(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_Z_2;
        targetAngle = degrees;
    }

    void rotate_Z_3(float degrees) {
        if (degrees != 0)
            ignoreKeyboardInput = true;
        lock_guard<mutex> l(cubeMutex);
        rotateFlag = ROTATE_Z_3;
        targetAngle = degrees;
    }
}