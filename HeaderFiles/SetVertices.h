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

const vec3 red = vec3(1.0f,0.0f,0.0f);
const vec3 white = vec3(1.0f,1.0f,1.0f);
const vec3 blue = vec3(0.0f,1.0f,1.0f);
const vec3 yellow = vec3(1.0f,1.0f,0.0f);
const vec3 green = vec3(0.0f,1.0f,0.0f);
const vec3 orange = vec3(1.0f,0.5f,0.0f);
const vec3 black = vec3(0.5f,0.5f,0.5f);

vec3 localCubeVertices[NUM_VERTICES / 3] = {
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
        vec3(-CUBE_LENGTH, -CUBE_LENGTH, CUBE_LENGTH)
};//Local Space //One Cube

vec3 Colors[36]={
        red,red,red,red,red,red,
        orange,orange,orange,orange,orange,orange,
        white,white,white,white,white,white,
        yellow,yellow,yellow,yellow,yellow,yellow,
        blue,blue,blue,blue,blue,blue,
        green,green,green,green,green,green,
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
    for(int i=0;i<NUM_CUBES;i++) {
        cubePositions[count] =
                vec3((cubeCentralVertices[count].x) * (2 * CUBE_LENGTH + GAP),
                     (cubeCentralVertices[count].y) * (2 * CUBE_LENGTH + GAP),
                     (cubeCentralVertices[count].z) * (2 * CUBE_LENGTH + GAP));
        count++;
    }
}

//int colors[] = {
//        //down,up,left,right,back,front
//        DOWN, NONE, LEFT, NONE, BACK, NONE,
//        DOWN, NONE, NONE, NONE, BACK, NONE,
//        DOWN, NONE, NONE, RIGHT, BACK, NONE,
//        DOWN, NONE, LEFT, NONE, NONE, NONE,
//        DOWN, NONE, NONE, NONE, NONE, NONE,
//        DOWN, NONE, NONE, RIGHT, NONE, NONE,
//        DOWN, NONE, LEFT, NONE, NONE, FRONT,
//        DOWN, NONE, NONE, NONE, NONE, FRONT,
//        DOWN, NONE, NONE, RIGHT, NONE, FRONT,
//        NONE, NONE, LEFT, NONE, BACK, NONE,
//        NONE, NONE, NONE, NONE, BACK, NONE,
//        NONE, NONE, NONE, RIGHT, BACK, NONE,
//        NONE, NONE, LEFT, NONE, NONE, NONE,
//        NONE, NONE, NONE, NONE, NONE, NONE,
//        NONE, NONE, NONE, RIGHT, NONE, NONE,
//        NONE, NONE, LEFT, NONE, NONE, FRONT,
//        NONE, NONE, NONE, NONE, NONE, FRONT,
//        NONE, NONE, NONE, RIGHT, NONE, FRONT,
//        NONE, UP, LEFT, NONE, BACK, NONE,
//        NONE, UP, NONE, NONE, BACK, NONE,
//        NONE, UP, NONE, RIGHT, BACK, NONE,
//        NONE, UP, LEFT, NONE, NONE, NONE,
//        NONE, UP, NONE, NONE, NONE, NONE,
//        NONE, UP, NONE, RIGHT, NONE, NONE,
//        NONE, UP, LEFT, NONE, NONE, FRONT,
//        NONE, UP, NONE, NONE, NONE, FRONT,
//        NONE, UP, NONE, RIGHT, NONE, FRONT,
//};
//
//vec3 magicCubeColors[NUM_CUBES * NUM_VERTICES / 3];
//int colorcounter = 0;
//void setColor() {
//    int counter = 0;
//    while (counter < NUM_CUBES * 6) {
//        for (int i = 0; i < 6; i++) {
//            switch (colors[counter]) {
//                case RIGHT:
//                    magicCubeColors[colorcounter++] = red;
//                    break;
//                case DOWN:
//                    magicCubeColors[colorcounter++] = white;
//                    break;
//                case FRONT:
//                    magicCubeColors[colorcounter++] = blue;
//                    break;
//                case UP:
//                    magicCubeColors[colorcounter++] = yellow;
//                    break;
//                case BACK:
//                    magicCubeColors[colorcounter++] = green;
//                    break;
//                case LEFT:
//                    magicCubeColors[colorcounter++] = orange;
//                    break;
//                case NONE:
//                    magicCubeColors[colorcounter++] = black;
//                    break;
//            }
//        }
//        counter++;
//    }
//    for(int i=0;i<NUM_CUBES * NUM_VERTICES / 3;i++){
////        cout<<magicCubeColors[i].x<<","<<magicCubeColors[i].y<<","<<magicCubeColors[i].z<<endl;
//    }
//}
//
//vec3 verticesWithColor[NUM_CUBES][72];
//
//void setVerticesWithColor(){
//    int counter = 0;
//    colorcounter = 0;
//    for(int i=0;i<NUM_CUBES;i++){
//        for(int j=0;j<36;j++){
//            verticesWithColor[i][counter] = localCubeVertices[j];
//            cout<<verticesWithColor[i][counter].x<<","<<verticesWithColor[i][counter].y<<","<<verticesWithColor[i][counter++].z<<",";
//            verticesWithColor[i][counter] = magicCubeColors[colorcounter++];
//            cout<<verticesWithColor[i][counter].x<<","<<verticesWithColor[i][counter].y<<","<<verticesWithColor[i][counter++].z<<","<<endl;
//        }
//        counter = 0;
//    }
//}
#endif