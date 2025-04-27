add_executable(gl_main main.cpp)
add_executable(gl_draw_arrays main_gl_draw_arrays.cpp)
add_executable(gl_different_vao_vbo main_different_vao_vbo.cpp)
add_executable(gl_two_color_program main_two_color_program.cpp)
add_executable(gl_texture main_texture.cpp)
add_executable(gl_transform main_transform.cpp)
add_executable(gl_coordinate main_coord.cpp)
add_executable(gl_camera main_camera.cpp)


# main.cpp
auto_link_to_gl(gl_main
  LIBS glad glfw common shader
  INCLUDES glad glfw common shader)
# main_gl_draw_arrays.cpp
auto_link_to_gl(gl_draw_arrays
  LIBS glad glfw common shader
  INCLUDES glad glfw common shader)
# main_different_vao_vbo.cpp
auto_link_to_gl(gl_different_vao_vbo
  LIBS glad glfw common shader
  INCLUDES glad glfw common shader)
# main_two_color_program.cpp
auto_link_to_gl(gl_two_color_program
  LIBS glad glfw common shader
  INCLUDES glfw glad common shader)
# main_texture
auto_link_to_gl(gl_texture
  LIBS glad glfw common shader
  INCLUDES glad glfw common shader)
# main_transform
auto_link_to_gl(gl_transform
  LIBS glad glfw common shader
  INCLUDES glad glfw common shader)
# main_coord.cpp
auto_link_to_gl(gl_coordinate
  LIBS glad glfw common shader
  INCLUDES glad glfw common shader)
# main_camera.cpp
auto_link_to_gl(gl_camera
  LIBS glad glfw shader
  INCLUDES glad glfw shader)
