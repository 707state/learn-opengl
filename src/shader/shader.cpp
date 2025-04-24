#include <shader/shader.h>
#include <fstream>
#include <sstream>
#include<iostream>
#include <string>
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // 从文件路径获取顶点/片段着色器
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        std::cout << "Trying to load shaders!\n";
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::cout<<"Trying to read from file!\n";
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode=fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout<<"Error::Shader::FILE_NOT_SUCCESSFULLY_READ"<<std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // Compile shader
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    LOGGING(vertex, GL_COMPILE_STATUS);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    LOGGING(fragment,GL_COMPILE_STATUS);
    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    LOGGING(ID, GL_LINK_STATUS);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::use() { glUseProgram(ID); }
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
