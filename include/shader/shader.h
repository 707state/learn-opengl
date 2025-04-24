#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#define LOGGING(x, type)                       \
  glGetShaderiv(x, type, &success);            \
    if (!success) {                               \
    glGetShaderInfoLog(x, 512, NULL, infoLog); \
    std::cout<<"Error: "<<infoLog<<std::endl;\
}
class Shader {
 public:
    unsigned int ID;
    Shader() = default;
    Shader(const char* vertexPath, const char* fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};


#endif
