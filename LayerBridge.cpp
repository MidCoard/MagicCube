#include "Layers/LogicLayer.cpp"
#include "Layers/RenderLayer.cpp"

void render(double elapsed) {
    Render::render(elapsed);
}

void updateGameState() {
    Logic::updateGameState();
}
void handleInput() {
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Render::getWindow()->getWindow(), true);
    }//退出游戏

    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        glfwSetInputMode(Render::getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Render::setFirstMouse(true);
    }
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE) {
        glfwSetInputMode(Render::getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }//捕捉鼠标

    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_P) == GLFW_PRESS){
        delete(Render::camera);
        Render::camera = new Camera(CAMERA_POSITION);
        XAxis = -normalize(cross(vec3(CAMERA_POSITION),YAxis));
        Render::currentModel = mat4(1.0f);
    }//恢复正视角

    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_RIGHT_ALT) == GLFW_PRESS){
        for(int i=0;i<NUM_CUBES;i++){
        Render::allCubesState[i] = mat4(1.0f);
        }
    }//还原魔方至初始状态
    if(!Render::ignoreKeyboardInput) {
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            Render::rotate_Y_1(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            Render::rotate_Y_1(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            Render::rotate_Y_2(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            Render::rotate_Y_2(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_Z) == GLFW_PRESS) {
            Render::rotate_Y_3(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_X) == GLFW_PRESS) {
            Render::rotate_Y_3(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_U) == GLFW_PRESS) {
            Render::rotate_X_1(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_J) == GLFW_PRESS) {
            Render::rotate_X_1(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_I) == GLFW_PRESS) {
            Render::rotate_X_2(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_K) == GLFW_PRESS) {
            Render::rotate_X_2(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_O) == GLFW_PRESS) {
            Render::rotate_X_3(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_L) == GLFW_PRESS) {
            Render::rotate_X_3(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
            Render::rotate_Z_1(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_0) == GLFW_PRESS) {
            Render::rotate_Z_1(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
            Render::rotate_Z_2(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_9) == GLFW_PRESS) {
            Render::rotate_Z_2(-90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
            Render::rotate_Z_3(90);
        }
        if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_8) == GLFW_PRESS) {
            Render::rotate_Z_3(-90);
        }
    }
}