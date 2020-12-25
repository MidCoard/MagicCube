#include "layers/LayerBridge.cpp"
#include "layers/RenderLayer.h"
#include "layers/LogicLayer.h"
#include "util.h"

using namespace std;

void initialize(char* state) {
    Logic::initLogicLayer();
    Render::initRenderLayer(state);
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

int main(int argc, char *argv[]) {
    if (argc > 1)
        initialize(argv[1]);
    else initialize((char*)"");
    if (isInitialize()) {
        double secsPerUpdate = 1.0 / 100.0;
        double previous = getTime();
        double steps = 0.0;
        double last = 0;
        while (!glfwWindowShouldClose(Render::getGLWindow()->getWindow())) {
            double loopStartTime = getTime();
            double elapsed = loopStartTime - previous;
            previous = loopStartTime;
            steps += elapsed;

            handleInput();

            while (steps >= secsPerUpdate) {
                updateGameState();
                steps -= secsPerUpdate;
            }
            render(elapsed);
            sync(loopStartTime);
            if (getTime() - last >= 1) {
                last++;
            }
        }
        Render::clear();
    }
}