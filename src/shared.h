#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <concepts>
#include <string>

#ifndef SHARED_H
#define SHARED_H


namespace shared {
namespace detail {
    void processInput(GLFWwindow *window);
}

void mainLoop(GLFWwindow *window, std::invocable<> auto render) {
  while (!glfwWindowShouldClose(window)) {
    detail::processInput(window);

    render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}

GLFWwindow *setupGlfwWindow();
unsigned int setupVertexShader(std::string const &source);
unsigned int setupFragmentShader(std::string const &source);
unsigned int setupShaderProgram(unsigned int vertexShader,
                                unsigned int fragmentShader);

int getNrAttributes();
}


#endif // SHARED_H
