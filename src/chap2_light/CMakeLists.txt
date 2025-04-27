add_executable(gl_light main_light.cpp)
auto_link_to_gl(gl_light
  LIBS glad glfw shader camera
  INCLUDES glad glfw shader camera)
add_executable(gl_diffuse main_diffuse.cpp)
auto_link_to_gl(gl_diffuse
  LIBS glad glfw shader camera
  INCLUDES glad glfw shader camera)
