#include "shader.h"

#include "file.h"
#include "shared.h"

using namespace shared;

Shader::Shader(std::filesystem::path const &vertexPath,
               std::filesystem::path const &fragmentPath)
    : Shader::Shader(getFileContents(vertexPath),
                     getFileContents(fragmentPath)) {}

Shader::Shader(const std::string &vertexSource,
               const std::string &fragmentSource) {
  auto vertexShader = setupVertexShader(vertexSource);
  auto fragmentShader = setupFragmentShader(fragmentSource);
  this->programId = setupShaderProgram(vertexShader, fragmentShader);
}

void Shader::use() const { glUseProgram(this->programId); }

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(this->programId, name.c_str()),
              static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glad_glGetUniformLocation(this->programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glad_glGetUniformLocation(this->programId, name.c_str()), value);
}
