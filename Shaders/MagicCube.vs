#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec4 Color;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Color = vec4(aColor,1.0f);
    gl_Position = projection * transform * view * vec4(FragPos, 1.0f);
}