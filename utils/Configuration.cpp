#include "Configuration.h"

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
        Colors[count++] = up.toVec3();
    for(int i=0;i<6;i++)
        Colors[count++] = down.toVec3();
    for(int i=0;i<6;i++)
        Colors[count++] = front.toVec3();
    for(int i=0;i<6;i++)
        Colors[count++] = back.toVec3();
    for(int i=0;i<6;i++)
        Colors[count++] = left.toVec3();
    for(int i=0;i<6;i++)
        Colors[count++] = right.toVec3();
}
