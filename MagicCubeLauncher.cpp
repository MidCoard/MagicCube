#include <cstdio>
#include "LayerBridge.cpp"
#include "util.cpp"

using namespace std;

void initialize() {

}

void sync(double loopStartTime) {
    float loopSlot = 1.0f / 50;
    double endTime = loopStartTime + loopSlot;
    while(getTime() < endTime) {
        sleep(1);
    }
}

int main() {
    initialize();
    double secsPerUpdate = 1.0 / 30.0;
    double previous = getTime();
    double steps = 0.0;
    while (true) {
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
    }
}