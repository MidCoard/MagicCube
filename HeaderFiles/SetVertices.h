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
};//Normal Vectors

Color logicColors[6] = {
        RED,
        ORANGE,
        WHITE,
        YELLOW,
        BLUE,
        GREEN
};

vec3 Colors[NUM_VERTICES];

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

void setColors(Color up,Color down,Color front,Color back,Color left,Color right) {
    int count=0;
    for(int i=0;i<6;i++){
        Colors[count++] = up.toVec3();
    }
    for(int i=0;i<6;i++){
        Colors[count++] = down.toVec3();
    }
    for(int i=0;i<6;i++){
        Colors[count++] = front.toVec3();
    }
    for(int i=0;i<6;i++){
        Colors[count++] = back.toVec3();
    }
    for(int i=0;i<6;i++){
        Colors[count++] = left.toVec3();
    }
    for(int i=0;i<6;i++){
        Colors[count++] = right.toVec3();
    }
}
#endif