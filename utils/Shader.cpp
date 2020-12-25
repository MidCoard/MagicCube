#include "Shader.h"

void Shader::setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const  {
    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
}

// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y);
}

// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y, z);
}

// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y, z, w);
}

// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}



Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
    glfwInit();

    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {

        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);
        stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
        exit(ErrorCode);
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    int vertexShader_success;
    int fragmentShader_success;
    int programLinking_success;
    char vertexShader_infoLog[InfoLogSize];
    char fragmentShader_infoLog[InfoLogSize];
    char programLinking_infoLog[InfoLogSize];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertexShader_success);
    if (!vertexShader_success) {
        glGetShaderInfoLog(vertex, InfoLogSize, nullptr, vertexShader_infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertexShader_infoLog << endl;
        exit(ErrorCode);
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &fragmentShader_success);
    if (!fragmentShader_success) {
        glGetShaderInfoLog(fragment, InfoLogSize, nullptr, vertexShader_infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentShader_infoLog << endl;
        exit(ErrorCode);
    }

    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertex);
    glAttachShader(ShaderProgramID, fragment);
    glLinkProgram(ShaderProgramID);

    glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &programLinking_success);
    if (!programLinking_success) {
        glGetProgramInfoLog(ShaderProgramID, InfoLogSize, nullptr, programLinking_infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << programLinking_infoLog << endl;
        exit(ErrorCode);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const {
    glUseProgram(ShaderProgramID);
}

unsigned int Shader::getProgramId() const {
    return ShaderProgramID;
}

Shader::~Shader() {
    glDeleteProgram(ShaderProgramID);
}