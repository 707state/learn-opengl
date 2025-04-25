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
# camera 库
add_library(camera
  SHARED
  src/camera/camera.cpp
  include/camera/camera.h)
target_link_libraries(camera
  PUBLIC
  glfw
)
target_include_directories(camera
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
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
  glfw
)

# Executable file should be linked here.
function(auto_link_to_gl TARGET)
  cmake_parse_arguments(ARG
    ""
    ""
    "LIBS;INCLUDES"
    ${ARGN})
  target_link_libraries(${TARGET} PUBLIC ${ARG_LIBS})
  target_link_libraries(${TARGET}
    PUBLIC
    ${ARG_INCLUDES})
endfunction()

add_subdirectory(src/chap1_intro/)
