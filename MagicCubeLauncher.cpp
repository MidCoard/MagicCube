#include <cstdio>
#include "LayerBridge.cpp"
#include "util.cpp"
#include "RenderPoint.h"

using namespace std;

void initialize() {
//    initRenderPoint();
    Logic::initLogicLayer();
    Render::initRenderLayer();
}

void sync(double loopStartTime) {
    float loopSlot = 1.0f / 300;
    double endTime = loopStartTime + loopSlot;
    while(getTime() < endTime) {
        sleepMS(1);
    }
}

bool isInitialize() {
    return Logic::isInitialize() && Render::isInitialize();
}

int main() {
    initialize();
    if (isInitialize()) {
        double secsPerUpdate = 1.0 / 100.0;
        double previous = getTime();
        double steps = 0.0;
        double last = 0;
        while (!glfwWindowShouldClose(Render::getWindow()->getWindow())) {
            double loopStartTime = getTime();
            double elapsed = loopStartTime - previous;
            previous = loopStartTime;
            steps += elapsed;

            handleInput();

            while (steps >= secsPerUpdate) {
                updateGameState();
                steps -= secsPerUpdate;
            }
            render();
            sync(loopStartTime);
            if (getTime() - last >= 1) {
                last++;
            }
        }
        Render::clear();
    }
}