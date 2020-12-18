//
// Created by 周蜀杰 on 2020/12/15.
//

#ifndef __RENDERLAYER_H
#define __RENDERLAYER_H

#include <glm/glm.hpp>

using namespace glm;

bool isStartGameLoop();

namespace Render {
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
}


#endif //TEST_RENDERLAYER_H
