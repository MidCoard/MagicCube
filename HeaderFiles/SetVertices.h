#ifndef MAGICCUBE_SETVERTICES_H
#define MAGICCUBE_SETVERTICES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Color.h"

#define CUBE_LENGTH 0.5f
#define GAP 0.03f

#define NUM_CUBES 27
#define NUM_VERTICES 36

using namespace glm;

const vec3 standardXAxis = vec3(1.0f, 0.0f, 0.0f);
const vec3 standardYAxis = vec3(0.0f, 1.0f, 0.0f);
const vec3 standardZAxis = vec3(0.0f, 0.0f, 1.0f);//旋转魔方时的旋转轴 它们是不变的

const Color red = Color(1.0f, 0.1f, 0.1f);
const Color white = Color(1.0f, 1.0f, 1.0f);
const Color blue = Color(0.1f, 0.6f, 1.0f);
const Color yellow = Color(1.0f, 1.0f, 0.1f);
const Color green = Color(0.1f, 1.0f, 0.1f);
const Color orange = Color(1.0f, 0.6f, 0.1f);
const Color black = Color(0.5f, 0.5f, 0.5f);

vec3 localCubeVertices[NUM_VERTICES] = {
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),

        vec3(-CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),

        vec3(-CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),

        vec3(CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),

        vec3(-CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH),

        vec3(-CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH),
        vec3(CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH),
};//Local Space //One Cube

vec3 normalVector[NUM_VERTICES]={
        -standardYAxis,
        -standardYAxis,
        -standardYAxis,
        -standardYAxis,
        -standardYAxis,
        -standardYAxis,

        standardYAxis,
        standardYAxis,
        standardYAxis,
        standardYAxis,
        standardYAxis,
        standardYAxis,

        -standardXAxis,
        -standardXAxis,
        -standardXAxis,
        -standardXAxis,
        -standardXAxis,
        -standardXAxis,

        standardXAxis,
        standardXAxis,
        standardXAxis,
        standardXAxis,
        standardXAxis,
        standardXAxis,

        -standardZAxis,
        -standardZAxis,
        -standardZAxis,
        -standardZAxis,
        -standardZAxis,
        -standardZAxis,

        standardZAxis,
        standardZAxis,
        standardZAxis,
        standardZAxis,
        standardZAxis,
        standardZAxis
};

Color Colors[36] = {
        red, red, red, red, red, red,
        orange, orange, orange, orange, orange, orange,
        white, white, white, white, white, white,
        yellow, yellow, yellow, yellow, yellow, yellow,
        blue, blue, blue, blue, blue, blue,
        green, green, green, green, green, green,
};

vec3 cubeCentralVertices[NUM_CUBES];

vec3 cubePositions[27];//World Space //27 Cubes

void setWorldSpace() {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                cubeCentralVertices[count++] = vec3(i, j, k);
            }
        }
    }
    count = 0;
    for (int i = 0; i < NUM_CUBES; i++) {
        cubePositions[count] =
                vec3((cubeCentralVertices[count].x) * (2 * CUBE_LENGTH + GAP),
                     (cubeCentralVertices[count].y) * (2 * CUBE_LENGTH + GAP),
                     (cubeCentralVertices[count].z) * (2 * CUBE_LENGTH + GAP));
        count++;
    }
}

enum cubeFace {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    BACK,
    FRONT
};
int colors[] = {
        //down,up,left,right,back,front
        DOWN, NONE, LEFT, NONE, BACK, NONE,
        DOWN, NONE, NONE, NONE, BACK, NONE,
        DOWN, NONE, NONE, RIGHT, BACK, NONE,
        DOWN, NONE, LEFT, NONE, NONE, NONE,
        DOWN, NONE, NONE, NONE, NONE, NONE,
        DOWN, NONE, NONE, RIGHT, NONE, NONE,
        DOWN, NONE, LEFT, NONE, NONE, FRONT,
        DOWN, NONE, NONE, NONE, NONE, FRONT,
        DOWN, NONE, NONE, RIGHT, NONE, FRONT,
        NONE, NONE, LEFT, NONE, BACK, NONE,
        NONE, NONE, NONE, NONE, BACK, NONE,
        NONE, NONE, NONE, RIGHT, BACK, NONE,
        NONE, NONE, LEFT, NONE, NONE, NONE,
        NONE, NONE, NONE, NONE, NONE, NONE,
        NONE, NONE, NONE, RIGHT, NONE, NONE,
        NONE, NONE, LEFT, NONE, NONE, FRONT,
        NONE, NONE, NONE, NONE, NONE, FRONT,
        NONE, NONE, NONE, RIGHT, NONE, FRONT,
        NONE, UP, LEFT, NONE, BACK, NONE,
        NONE, UP, NONE, NONE, BACK, NONE,
        NONE, UP, NONE, RIGHT, BACK, NONE,
        NONE, UP, LEFT, NONE, NONE, NONE,
        NONE, UP, NONE, NONE, NONE, NONE,
        NONE, UP, NONE, RIGHT, NONE, NONE,
        NONE, UP, LEFT, NONE, NONE, FRONT,
        NONE, UP, NONE, NONE, NONE, FRONT,
        NONE, UP, NONE, RIGHT, NONE, FRONT,
};

//vec3 magicCubeColors[NUM_CUBES][NUM_VERTICES];
//
//void setColor() {
//    int counter = 0;
//    int counter1 = 0;
//    int colorCounter = 0;
//    while (counter < NUM_CUBES * 6) {
//        for (int i = 0; i < 6; i++) {
//            switch (colors[counter]) {
//                case RIGHT:
//                    magicCubeColors[colorCounter][counter1++] = red;
//                    break;
//                case DOWN:
//                    magicCubeColors[colorCounter][counter1++] = white;
//                    break;
//                case FRONT:
//                    magicCubeColors[colorCounter][counter1++] = blue;
//                    break;
//                case UP:
//                    magicCubeColors[colorCounter][counter1++] = yellow;
//                    break;
//                case BACK:
//                    magicCubeColors[colorCounter][counter1++] = green;
//                    break;
//                case LEFT:
//                    magicCubeColors[colorCounter][counter1++] = orange;
//                    break;
//                case NONE:
//                    magicCubeColors[colorCounter][counter1++] = black;
//                    break;
//            }
//            if (counter1 == 36) counter1 = 0;
//        }
//        if ((counter + 1) / 6 == 0) colorCounter++;
//        counter++;
//    }
//    cout << sizeof(magicCubeColors) << endl;
//    cout << sizeof(magicCubeColors) / sizeof(float) << endl;
//}

#endif