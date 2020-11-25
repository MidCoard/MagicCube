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
    short getR() const {
        return r;
    }

    short getG() const {
        return g;
    }

    short getB() const {
        return b;
    }

public:
    Color(short r,short g,short b) {
        this->r;
        this->g;
        this->b;
    }
};


const Color BLUE = Color(0,0,255);
const Color GREEN = Color(0,255,0);
const Color ORANGE = Color(255,165,0);
const Color RED = Color(255,0,0);
const Color YELLOW = Color(255,255,0);
const Color WHITE = Color(255,255,255);


#endif //MAGICCUBE_COLOR_H
