#include "Configuration.h"

const vec3 STANDARD_X_AXIS = vec3(1.0f, 0.0f, 0.0f);
const vec3 STANDARD_Y_AXIS = vec3(0.0f, 1.0f, 0.0f);
const vec3 STANDARD_Z_AXIS = vec3(0.0f, 0.0f, 1.0f);//旋转魔方时的旋转轴 它们是不变的

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
};//Local Space //一个方块的坐标

vec3 normalVector[NUM_VERTICES]={
        -STANDARD_Y_AXIS,
        -STANDARD_Y_AXIS,
        -STANDARD_Y_AXIS,
        -STANDARD_Y_AXIS,
        -STANDARD_Y_AXIS,
        -STANDARD_Y_AXIS,

        STANDARD_Y_AXIS,
        STANDARD_Y_AXIS,
        STANDARD_Y_AXIS,
        STANDARD_Y_AXIS,
        STANDARD_Y_AXIS,
        STANDARD_Y_AXIS,

        -STANDARD_X_AXIS,
        -STANDARD_X_AXIS,
        -STANDARD_X_AXIS,
        -STANDARD_X_AXIS,
        -STANDARD_X_AXIS,
        -STANDARD_X_AXIS,

        STANDARD_X_AXIS,
        STANDARD_X_AXIS,
        STANDARD_X_AXIS,
        STANDARD_X_AXIS,
        STANDARD_X_AXIS,
        STANDARD_X_AXIS,

        -STANDARD_Z_AXIS,
        -STANDARD_Z_AXIS,
        -STANDARD_Z_AXIS,
        -STANDARD_Z_AXIS,
        -STANDARD_Z_AXIS,
        -STANDARD_Z_AXIS,

        STANDARD_Z_AXIS,
        STANDARD_Z_AXIS,
        STANDARD_Z_AXIS,
        STANDARD_Z_AXIS,
        STANDARD_Z_AXIS,
        STANDARD_Z_AXIS
};//Normal Vectors

Color logicColors[6] = {
        RED,
        ORANGE,
        WHITE,
        YELLOW,
        BLUE,
        GREEN
};

vec3 colors[NUM_VERTICES];

vec3 cubeCentralVertices[NUM_CUBES];

vec3 cubePositions[27];//World Space //27 Cubes
void defaultVertices() {
    int count = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
                cubeCentralVertices[count++] = vec3(i, j, k);
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
    for(int i=0;i<6;i++)
        colors[count++] = up.toVec3();
    for(int i=0;i<6;i++)
        colors[count++] = down.toVec3();
    for(int i=0;i<6;i++)
        colors[count++] = front.toVec3();
    for(int i=0;i<6;i++)
        colors[count++] = back.toVec3();
    for(int i=0;i<6;i++)
        colors[count++] = left.toVec3();
    for(int i=0;i<6;i++)
        colors[count++] = right.toVec3();
}
