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

extern const vec3 STANDARD_X_AXIS;
extern const vec3 STANDARD_Y_AXIS;
extern const vec3 STANDARD_Z_AXIS;

extern Color logicColors[6];

extern vec3 localCubeVertices[NUM_VERTICES];

extern vec3 normalVector[NUM_VERTICES];

extern vec3 colors[NUM_VERTICES];

extern vec3 cubePositions[27];

void defaultVertices();

void setColors(Color up,Color down,Color front,Color back,Color left,Color right);
#endif