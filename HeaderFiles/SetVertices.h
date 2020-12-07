#ifndef MAGICCUBE_SETVERTICES_H
#define MAGICCUBE_SETVERTICES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CUBE_LENGTH 0.5f
#define GAP 0.1f

#define NUM_CUBES 27
#define NUM_VERTICES 108

using namespace glm;

float cubeVertices[NUM_VERTICES] = {
        -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        -CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,

        -CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,

        -CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,

        CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,

        -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, -CUBE_LENGTH, -CUBE_LENGTH,

        -CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, CUBE_LENGTH, CUBE_LENGTH,
        -CUBE_LENGTH, CUBE_LENGTH, -CUBE_LENGTH
};      //Local Space //One Cube

vec3 cubePositions[3][3][3];//World Space //27 Cubes

vec3 cubeCentralVertices[NUM_CUBES];

void setCubeCentralVertices() {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                cubeCentralVertices[count++] = vec3(i, j, k);
            }
        }
        cout << endl;
    }
}
void setMagicCubeVertices(){
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cubePositions[i][j][k] =
                        vec3((cubeCentralVertices[count].x) * (2 * CUBE_LENGTH + GAP),
                             (cubeCentralVertices[count].y) * (2 * CUBE_LENGTH + GAP),
                             (cubeCentralVertices[count].z) * (2 * CUBE_LENGTH + GAP));
                count++;
            }
        }
    }
}
void ROTATE(float degrees){
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                vec4 cubeCentralVerticesv4 = vec4(cubeCentralVertices[i],1.0f);

            }
        }
    }
}

#endif