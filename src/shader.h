#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class Shader {
public:
    unsigned int programId;

    explicit Shader(std::filesystem::path const &vertexPath, std::filesystem::path const &fragmentPath);
    Shader(std::string const &vertexSource, std::string const &fragmentSource);
    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif // SHADER_H
