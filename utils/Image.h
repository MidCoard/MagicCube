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

Shader *imageShader;
GLuint imageVAO, imageVBO, textureVBO;
GLuint texture;


vec3 imageVertices[] = {
        vec3(-1.0f, 1.0f, 0.0f),
        vec3(1.0f, 1.0f, 0.0f),
        vec3(1.0f, -1.0f, 0.0f),
        vec3(1.0f, -1.0f, 0.0f),
        vec3(-1.0f, 1.0f, 0.0f),
        vec3(-1.0f, -1.0f, 0.0f)
};

vec2 textureVertices[] = {
        vec2(0.0f,1.0f),
        vec2(1.0f,1.0f),
        vec2(1.0f,0.0f),
        vec2(1.0f,0.0f),
        vec2(0.0f,1.0f),
        vec2(0.0f,0.0f)
};

void initImage();
void renderImage(vec3 position, float scaleX, float scaleY, float alpha, mat4 view, mat4 projection, char* imagePath);
#endif