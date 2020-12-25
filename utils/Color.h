#ifndef MAGICCUBE_COLOR_H
#define MAGICCUBE_COLOR_H

#include "glm/glm.hpp"

using namespace glm;

class Color {
private:
    short r;
    short g;
    short b;
public:
    short getR() const;
    short getG() const;
    short getB() const;
    Color(vec3 vec);
    Color(short r,short g,short b);
    vec3 toVec3() const;
};

class ColorRGBA : public Color {
private:
    float a;
    float*list;
public:
    ColorRGBA(short r,short g,short b,float a);
    ColorRGBA(float r,float g,float b,float a);
    float * getAsList() const;
    ~ColorRGBA();
    float getA() const;
};


const Color BLUE = Color(0,80,255);
const Color GREEN = Color(80,255,80);
const Color ORANGE = Color(255,165,0);
const Color RED = Color(255,80,80);
const Color YELLOW = Color(255,255,80);
const Color WHITE = Color(230,230,230);


#endif
