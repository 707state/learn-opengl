#include <array>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "common/util.h"
#include "shader/shader.h"
constexpr static unsigned int SCR_WIDTH = 800;
constexpr static unsigned int SRC_HEIGHT = 600;

//clang-format off
float vertices[] = {
    // 位置              // 颜色
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};
//clang-format on

int main() {
    //Initialize glfw stuff
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == nullptr) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Initialize glad stuff
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // 设置为线框模式
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    Shader myShader("./vertexShader.glsl", "./fragmentShader.glsl");
    // VAO是顶点数组对象，可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中，好处是，当配置顶点属性指针时，只需要将调用执行一次，之后再绘制无力只需要绑定对应的VAO就可以。
    // EBO，元素缓冲对象。用EBO可以设定绘制这些顶点的顺序，也就是说，不需要重复渲染就可以绘制出一个三角形。
    unsigned int VAO, VBO;
    //unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.7f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        myShader.use();
        glBindVertexArray(VAO);
        myShader.setFloat("xOffset", 0.4f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
