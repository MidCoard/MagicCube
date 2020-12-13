#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightModel;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =  projection * view * lightModel * transform * vec4(aPos, 1.0);
}