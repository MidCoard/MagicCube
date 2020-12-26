#ifndef MAGICCUBE_UTIL_H
#define MAGICCUBE_UTIL_H

#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;

void sleepMS(int microseconds);
double getTime();
int exec(const char *in, char *out);
bool endsWith(string str,string sub);
int getAnswer(char sig);
char getAnswer(int sig);
#endif
