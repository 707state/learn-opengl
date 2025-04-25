#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

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
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name,float x,float y)const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z,float w) const;
    void setMat2(const std::string& name, const glm::mat2& value) const;
    void setMat3(const std::string& name, const glm::mat3& value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

};


#endif
