#ifndef MAGICCUBE_VERTICES_CONFIGURATION_H
#define MAGICCUBE_VERTICES_CONFIGURATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Color.h"

#define CUBE_LENGTH 0.5f
#define GAP 0.03f

#define NUM_CUBES 27
#define NUM_VERTICES 36

using namespace glm;

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
};//Local Space //One Cube

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

vec3 Colors[NUM_VERTICES];

vec3 cubeCentralVertices[NUM_CUBES];

vec3 cubePositions[27];//World Space //27 Cubes

void defaultVertices();

void setColors(Color up,Color down,Color front,Color back,Color left,Color right);
#endif