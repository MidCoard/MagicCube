#include "Layers/LogicLayer.cpp"
#include "Layers/RenderLayer.cpp"

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;
int count6 = 0;
int count7 = 0;
int count8 = 0;
int spacePressCount = 0;

void render(double elapsed) {
    if (!StartGameLoop && !ifHelp &&!ifDeveloper) Render::startMenu();
    if (ifPause && !ifHelp) Render::pause();
    if ((ifHelp||ifDeveloper) && ifPause || spacePressCount == 0 && (ifHelp||ifDeveloper)) Render::help();
    if (StartGameLoop && !ifPause) Render::GameLoop(elapsed);
    if (ifBackToTitle) {
        ifHelp=false;
        ifPause=false;
        ifDeveloper=false;
        StartGameLoop = false;
        ifBackToTitle = false;
        spacePressCount=0;
        Render::startMenu();
    }
}

void updateGameState() {
    Logic::updateGameState();
}

void handleInput() {
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Render::getGLWindow()->getWindow(), true);
    }//退出游戏

    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        glfwSetInputMode(Render::getGLWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Render::setFirstMouse(true);
    }
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_RELEASE) {
        glfwSetInputMode(Render::getGLWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }//捕捉鼠标

    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_P) == GLFW_PRESS) {
        delete (Render::camera);
        Render::camera = new Camera(CAMERA_POSITION);
        XAxis = -normalize(cross(vec3(CAMERA_POSITION), YAxis));
        Render::currentModel = mat4(1.0f);
    }//恢复正视角
#ifdef DEBUG
    if (glfwGetKey(Render::getWindow()->getWindow(), GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
        Render::resetStates();
    }//还原魔方至初始状态
#endif
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        count1++;
        if (count1 == 1 && spacePressCount == 0) {
            StartGameLoop = true;
            ifBackToTitle = false;
            spacePressCount++;
        }
        if (count1 == 1 && spacePressCount > 1) {
            ifPause = !ifPause;
        }
        if (StartGameLoop) spacePressCount++;
    }//开始游戏
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE) {
        count1 = 0;
    }
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_H) == GLFW_PRESS && (!StartGameLoop || ifPause)) {
        count2++;
        if (count2 == 1) {
            ifHelp = !ifHelp;
        }
    }
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_H) == GLFW_RELEASE && (!StartGameLoop || ifPause)) {
        count2 = 0;
    }//帮助界面
     if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_G) == GLFW_PRESS && (!StartGameLoop && !ifPause)) {
        count8++;
        if (count8 == 1) {
            ifDeveloper = !ifDeveloper;
        }
    }
    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_G) == GLFW_RELEASE && (!StartGameLoop && !ifPause)) {
        count8 = 0;
    }//开发者信息界面

    if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_B) == GLFW_PRESS) {
        Logic::clearBlocking();
    }

    if (Logic::isInSelecting()) {
        if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_0) == GLFW_PRESS) {
            Logic::setMode(0);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
            Logic::setMode(1);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
            Logic::setMode(2);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
            Logic::setMode(3);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_4) == GLFW_PRESS) {
            Logic::setMode(4);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_5) == GLFW_PRESS) {
            Logic::setMode(5);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_6) == GLFW_PRESS) {
            Logic::setMode(6);
        }
        return;
    }

    if (!Render::ignoreKeyboardInput && StartGameLoop && !Logic::inSolving && !Logic::inShuffling) {
        if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            Render::rotate_Y_1(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            Render::rotate_Y_1(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            Render::rotate_Y_2(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_S) == GLFW_PRESS &&
                   !glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            Render::rotate_Y_2(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_Z) == GLFW_PRESS) {
            Render::rotate_Y_3(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_X) == GLFW_PRESS) {
            Render::rotate_Y_3(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_U) == GLFW_PRESS) {
            Render::rotate_X_1(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_J) == GLFW_PRESS) {
            Render::rotate_X_1(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_I) == GLFW_PRESS) {
            Render::rotate_X_2(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_K) == GLFW_PRESS) {
            Render::rotate_X_2(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_O) == GLFW_PRESS) {
            Render::rotate_X_3(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_L) == GLFW_PRESS) {
            Render::rotate_X_3(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
            Render::rotate_Z_1(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_0) == GLFW_PRESS) {
            Render::rotate_Z_1(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
            Render::rotate_Z_2(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_9) == GLFW_PRESS) {
            Render::rotate_Z_2(-90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
            Render::rotate_Z_3(90);
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_8) == GLFW_PRESS) {
            Render::rotate_Z_3(-90);
        }
        if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_V) == GLFW_PRESS) {
            count3++;
            if (count3 == 1) {
                if (!Logic::inShuffling && !Logic::inSolving) {
                    Logic::solve(false);
                    Logic::setMode(1);
                }
            }
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_V) == GLFW_RELEASE) {
            count3 = 0;
        }
        if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_F) == GLFW_PRESS) {
            count4++;
            if (count4 == 1) {
                if (!Logic::inShuffling && !Logic::inSolving) {
                    Logic::solve(true);
                }
            }
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_F) == GLFW_RELEASE) {
            count4 = 0;
        }
        if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_C) == GLFW_PRESS) {
            count5++;
            if (count5 == 1) {
                if (!Logic::inShuffling && !Logic::inSolving)
                    Logic::shuffle();
            }
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_C) == GLFW_RELEASE) {
            count5 = 0;
        }
        if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_S) == GLFW_PRESS &&
            glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            count6++;
            if (count6 == 1) {
                Logic::saveState();
            }
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_S) == GLFW_RELEASE &&
                   glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
            count6 = 0;
        }if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_T) == GLFW_PRESS) {
            count7++;
            if (count7 == 1) {
                ifBackToTitle = true;
            }
        } else if (glfwGetKey(Render::getGLWindow()->getWindow(), GLFW_KEY_T) == GLFW_RELEASE) {
            count7 = 0;
        }
    }
}