#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "shared.h"

const float triangleA[] = {
    0.0f,  0.0f,  0.0f, // first triangle
    -1.0f, -1.0f, 0.0f, //
    -1.0f, 1.0f,  0.0f, //
};

const float triangleB[] = {
    0.0f, 0.0f,  0.0f, // second triangle
    1.0f, -1.0f, 0.0f, //
    0.0f, -1.0f, 0.0f  //
};

auto setupData(const float *data, size_t size) {
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // copies data to currently bound buffer
  glBufferData(GL_ARRAY_BUFFER, size, data,
               GL_STATIC_DRAW // data is only set once
  );
  return VBO;
}

auto vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z,
      1.0  // perspective division (?)
    );
}
)";

auto fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

void linkVertexAttributes() {
  glVertexAttribPointer(
      0,                 // what vertex attribute we want to configure
      3,                 // size of vertex attribute
      GL_FLOAT,          // type of data
      GL_FALSE,          // if data is to be normalized
      3 * sizeof(float), // stride (space between vertex attributes)
      0                  // offset
  );
  glEnableVertexAttribArray(0);
}

int main() {
  auto window = shared::setupGlfwWindow();

  auto vertexShader = shared::setupVertexShader(&vertexShaderSource);
  auto fragmentShader = shared::setupFragmentShader(&fragmentShaderSource);
  auto shaderprogram = shared::setupShaderProgram(vertexShader, fragmentShader);

  unsigned int VAO[2];
  glGenVertexArrays(2, VAO);
  glBindVertexArray(VAO[0]);

  setupData(triangleA, sizeof(triangleA));
  linkVertexAttributes();

  glBindVertexArray(VAO[1]);

  setupData(triangleB, sizeof(triangleB));
  linkVertexAttributes();

  shared::mainLoop(window, [=]() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderprogram);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  });
}