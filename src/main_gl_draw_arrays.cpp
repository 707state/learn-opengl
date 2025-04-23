#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "common/util.h"
constexpr static unsigned int SRC_WIDTH = 800;
constexpr static unsigned int SRC_HEIGHT=600;
//This file is used to finish the exercise 1.

// shader source
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
    "}\n\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
    "}\n\0";

int main() {
    // Init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
    // create glfw window
    GLFWwindow *window = glfwCreateWindow(
                                          SRC_WIDTH, SRC_HEIGHT, "Learn OpenGL gl draw arrays", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }
    // create context
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      return -1;
    }
    // build and compile shader
    // 顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, & vertexShaderSource,nullptr);
    glCompileShader(vertexShader);
    // check if shader compiled successfully
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        return -1;
    }
    // 片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1,& fragmentShaderSource,nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        return -1;
    }
    // 链接
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // 设置顶点数据以及顶点属性
    // clang-format off
    float vertices[] = {
        -0.9f,-0.5f,0.0f,
        -0.0f,-0.5f,0.0f,
        -0.45f,0.5f,0.0f,
        0.0f,-0.5f,0.0f,
        0.9f,-0.5f,0.0f,
        0.45f,0.5f,0.0f
    };
    // clang-format on
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // 首先要绑定顶点数组对象，再去绑定并设置顶点缓冲区，最后再设置顶点属性。
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    // 将VBO通过glVertexAttribPointer注册为顶点属性对应的VBO，这样之后就可以安全地解绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        // 在这个程序里面，虽然VAO只被使用到了一次，也就是说可以移动到渲染之前，但是为了让逻辑清晰，还是写到渲染内部
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
