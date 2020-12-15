#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SetVertices.h"

#define EPS 1E-8

using namespace glm;

class ColorMat {

private:
    Color colors[6];
public:
    ColorMat() {}
    ColorMat(Color up,Color down,Color left,Color right,Color front,Color back) {
        colors[0] = up;
        colors[1] = down;
        colors[2] = left;
        colors[3] = right;
        colors[4] = front;
        colors[5] = back;
    }

    Color getUp() {
        return colors[0];
    }

    Color getDown() {
        return colors[1];
    }

    Color getLeft() {
        return colors[2];
    }

    Color getRight() {
        return colors[3];
    }

    Color getFront() {
        return colors[4];
    }

    Color getBack() {
        return colors[5];
    }
};

ColorMat NULL_COLORMAT;

mat4 CubeState[24];

map<mat4,ColorMat> mp;

ColorMat getColorMat(mat4 mt) {
    for (int i = 0;i<24;i++) {
        bool flag = false;
        for (int j = 0;j<4;j++) {
            for (int k = 0; k < 4; k++)
                if (abs(mt[j][k] - CubeState[i][j][k]) >= EPS) {
                    flag = true;
                    break;
                }
            if (flag)
                break;
        }
        if (!flag)
            return mp[CubeState[i]];
    }
    return NULL_COLORMAT;
}


void initMatrix() {


    mat4 state;
    mp[state] = ColorMat(RED,RED,RED,RED,RED,RED);
}