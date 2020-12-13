//
// Created by Ken on 2020/11/24.
//

#ifndef MAGICCUBE_COLOR_H
#define MAGICCUBE_COLOR_H


class Color {
private:
    short r;
    short g;
    short b;
public:
    short getR() {
        return r;
    }

    short getG() {
        return g;
    }

    short getB() {
        return b;
    }

public:
    Color(short r,short g,short b) {
        this->r;
        this->g;
        this->b;
    }

    vec3 toVec3() {
        return vec3(r/255,g/255,b/255);
    }
};


Color BLUE = Color(0,0,255);
Color GREEN = Color(0,255,0);
Color ORANGE = Color(255,165,0);
Color RED = Color(255,0,0);
Color YELLOW = Color(255,255,0);
Color WHITE = Color(255,255,255);


#endif //MAGICCUBE_COLOR_H
