#include "Color.h"

short Color::getR() const {
    return r;
}

short Color::getG() const {
    return g;
}

short Color::getB() const {
    return b;
}

Color::Color(vec3 vec) {
this->r = vec.x * 255;
this->g = vec.y * 255;
this->b = vec.z * 255;
}

Color::Color(short r,short g,short b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

vec3 Color::toVec3() const {
    return vec3(r/255.0,g/255.0,b/255.0);
}

ColorRGBA::ColorRGBA(short r, short g, short b, float a):Color(r,g,b) {
    this->a = a;
    list = (float *)malloc(sizeof(float) * 4);
}

ColorRGBA::ColorRGBA(float r, float g, float b, float a) :Color(r*255,g*255,b*255) {
    this->a = a;
    list = (float *)malloc(sizeof(float) * 4);
}

ColorRGBA::~ColorRGBA() {
    free(list);
}

float * ColorRGBA::getAsList() const {
    list[0] = getR();
    list[1] = getG();
    list[2] = getB();
    list[3] = getA();
    return list;
}

float ColorRGBA::getA() const {
    return this->a;
}