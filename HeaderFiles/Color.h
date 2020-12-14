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
        this->r = r;
        this->g = g;
        this->b = b;
    }

    vec3 toVec3() const {
        return vec3(r/255.0,g/255.0,b/255.0);
    }
};


const Color BLUE = Color(0,80,255);
const Color GREEN = Color(80,255,80);
const Color ORANGE = Color(255,165,0);
const Color RED = Color(255,80,80);
const Color YELLOW = Color(255,255,80);
const Color WHITE = Color(230,230,230);


#endif //MAGICCUBE_COLOR_H
