cmake_minimum_required(VERSION 3.10)
project(learn_opengl)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(glfw3 REQUIRED "/opt/homebrew/opt/glfw")

file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 为glad创建独立的库
add_library(glad
  src/glad/glad.c
  include/KHR/khrplatform.h
  include/glad/glad.h)
target_include_directories(glad
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  glad
  glfw)
target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
