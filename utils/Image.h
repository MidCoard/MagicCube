#ifndef MAGICCUBE_IMAGE_H
#define MAGICCUBE_IMAGE_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include "GLWindows.h"
#include "Shader.h"

using namespace glm;

extern Shader *imageShader;
extern GLuint imageVAO, imageVBO, textureVBO;
extern GLuint texture;


extern vec3 imageVertices[];

extern vec2 textureVertices[];

void initImage();
void renderImage(vec3 position, float scaleX, float scaleY, float alpha, mat4 view, mat4 projection, char* imagePath);
#endif