#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTex;

out vec3 Tex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main(){
    gl_Position =  vec4(aPos,1.0f);
    Tex = aTex;
}