#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

using namespace std;

MagicCube magicCube;

void sleep(int microseconds) {
    this_thread::sleep_for(chrono::microseconds(microseconds));
}

double getTime() {
    return glfwGetTime();
}
