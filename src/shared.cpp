#include "shared.h"

#include <concepts>
#include <iostream>

namespace shared {
namespace detail {
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
} // namespace detail

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLFWwindow *setupGlfwWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int const windowWidth = 800;
  int const windowHeight = 600;

  GLFWwindow *window =
      glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
  if (window == nullptr) {
    glfwTerminate();
    throw new std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw new std::runtime_error("Failed to initialize GLAD");
  }

  return window;
}

unsigned int setupVertexShader(char const **source) {
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, source, nullptr);
  glCompileShader(vertexShader);

  int success = 0;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "verter shader info: " << infoLog << '\n';
    throw std::runtime_error("Failed to compile shader");
  }
  return vertexShader;
}

unsigned int setupFragmentShader(char const **source) {
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, source, nullptr);
  glCompileShader(fragmentShader);

  int success = 0;
  char infoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

    std::cerr << "framgent shader info: " << infoLog << '\n';

    throw std::runtime_error("Failed to compile fragment shader");
  }

  return fragmentShader;
}

unsigned int setupShaderProgram(unsigned int vertexShader,
                                unsigned int fragmentShader) {
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success = 0;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "link program info: " << infoLog << '\n';
    throw new std::runtime_error("Failed to link program");
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}
} // namespace shared
