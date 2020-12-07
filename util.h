#ifndef UTIL_H
#define UTIL_H
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

#define UP_ROW_1 0
#define UP_ROW_2 1
#define UP_ROW_3 2
#define DOWN_ROW_1 3
#define DOWN_ROW_2 4
#define DOWN_ROW_3 5
#define LEFT_COLUMN_1 6
#define LEFT_COLUMN_2 7
#define LEFT_COLUMN_3 8
#define RIGHT_COLUMN_1 9
#define RIGHT_COLUMN_2 10
#define RIGHT_COLUMN_3 11

using namespace std;

void sleepMS(int microseconds) {
    this_thread::sleep_for(chrono::microseconds(microseconds));
}

double getTime() {
    return glfwGetTime();
}
#endif
