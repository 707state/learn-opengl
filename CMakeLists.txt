cmake_minimum_required(VERSION 3.10)
project(learn_opengl)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable so lib
option(BUILD_SHARED_LIBS "docstring" ON)

# 全局构建类型设置
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

find_package(glfw3 REQUIRED "/opt/homebrew/opt/glfw")

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(gl_draw_arrays src/main_gl_draw_arrays.cpp)
add_executable(gl_different_vao_vbo src/main_different_vao_vbo.cpp)
add_executable(gl_two_color_program src/main_two_color_program.cpp)
add_executable(gl_texture src/main_texture.cpp)
# 添加头文件目录
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 为glad创建独立的库
add_library(glad SHARED
  src/glad/glad.c
  include/KHR/khrplatform.h
  include/glad/glad.h)
target_include_directories(glad
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)
# common 库
add_library(common
  SHARED
  src/common/util.cpp
  include/common/util.h
)

target_include_directories(common
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(common PRIVATE
  glad
  glfw
)

add_library(shader
  SHARED
  src/shader/shader.cpp
  include/shader/shader.h
  src/glad/glad.c
)

target_include_directories(shader
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(shader PRIVATE
  glad
)

# Executable file should be linked here.
function(auto_link_to_gl TARGET)
  target_link_libraries(${TARGET} PRIVATE glad glfw common shader)
  target_include_directories(${TARGET}
    PUBLIC
    glad
    glfw
    common
    shader)
endfunction()

# main.cpp
auto_link_to_gl(${PROJECT_NAME})
# main_gl_draw_arrays.cpp
auto_link_to_gl(gl_draw_arrays)
# main_different_vao_vbo.cpp
auto_link_to_gl(gl_different_vao_vbo)
# main_two_color_program.cpp
auto_link_to_gl(gl_two_color_program)
# main_texture
auto_link_to_gl(gl_texture)
