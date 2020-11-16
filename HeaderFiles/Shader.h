#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define InfoLogSize 512
#define ErrorCode -1

using namespace std;

class Shader
{
    private:
        unsigned int ShaderProgramID;
    public:
        Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
        ~Shader();

        void use();

        void setBool(const string &name, bool value) const;
        void setInt(const string &name, int value) const;
        void setFloat(const string &name, float value) const;
        unsigned int getProgramId();
};

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    glfwInit();

    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try
    {

        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);
        stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
        exit(ErrorCode);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    int  vertexShader_success;
    int  fragmentShader_success;
    int  programLinking_success;
    char vertexShader_infoLog[InfoLogSize];
    char fragmentShader_infoLog[InfoLogSize];
    char programLinking_infoLog[InfoLogSize];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertexShader_success);
    if(!vertexShader_success)
    {
        glGetShaderInfoLog(vertex, InfoLogSize, nullptr, vertexShader_infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertexShader_infoLog << endl;
        exit(ErrorCode);
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode,nullptr);
    glCompileShader(fragment);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &fragmentShader_success);
    if(!fragmentShader_success)
    {
        glGetShaderInfoLog(fragment, InfoLogSize, nullptr, vertexShader_infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentShader_infoLog << endl;
        exit(ErrorCode);
    }

    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertex);
    glAttachShader(ShaderProgramID, fragment);
    glLinkProgram(ShaderProgramID);

    glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &programLinking_success);
    if(!programLinking_success)
    {
        glGetProgramInfoLog(ShaderProgramID, InfoLogSize, nullptr, programLinking_infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << programLinking_infoLog << endl;
        exit(ErrorCode);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ShaderProgramID);
}
void Shader::setBool(const string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), (int)value);
}
void Shader::setInt(const string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
}
void Shader::setFloat(const string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
}
unsigned int Shader::getProgramId() {
    return ShaderProgramID;
}
Shader::~Shader() {
    glDeleteProgram(ShaderProgramID);
}

#endif