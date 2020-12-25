#ifndef MAGICCUBE_RENDER_LAYER_H
#define MAGICCUBE_RENDER_LAYER_H

#include <mutex>
#include "Shader.h"
#include "GLWindows.h"
#include "Camera.h"
#include "Configuration.h"
#include "Image.h"
#include "LogicLayer.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "MagicCube"

#define NUM_READIN 3
#define STRIDE(steps) steps * sizeof(float)
#define OFFSET_NULL nullptr
#define NO_JUMP 0
#define OFFSET(steps) (void*)steps  //使代码可读性增强



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

using namespace std;
using namespace glm;


namespace Render {

    bool isStartGameLoop();

    mat4 * getCubeState(int x, int y, int z);

    bool isIgnoreKeyboardInput();

    void rotate_X_1(float degrees);

    void rotate_X_2(float degrees);

    void rotate_X_3(float degrees);

    void rotate_Y_1(float degrees);

    void rotate_Y_2(float degrees);

    void rotate_Y_3(float degrees);

    void rotate_Z_1(float degrees);

    void rotate_Z_2(float degrees);

    void rotate_Z_3(float degrees);

    void resetStates();

    void startMenu();

    void pauseMenu();

    void helpMenu();

    void attribPointer();

    void setMagicCubeMatrix();

    void gameLoop(double);

    void clear();

    void mouseCallback(GLFWwindow *, double, double);

    void scrollCallback(GLFWwindow *, double, double);

    GLWindow* getGLWindow();

    bool isPause();

    bool isHelp();

    bool isDeveloper();

    bool isBackToTitle();

    bool isOpenFileSuccess();

    void setBackToTitle(bool);

    void setPause(bool);

    void setHelp(bool);

    void setDeveloper(bool);

    void setStartGameLoop(bool);

    void setFirstMouse(bool);

    Camera* getCamera();

    void setCamera(Camera*);

    void setCurrentModel(mat4);

	bool isInitialize();

	void initRenderLayer(char*);
}


#endif
