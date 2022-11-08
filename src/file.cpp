#include "file.h"

#include <fmt/core.h>
#include <fstream>

std::string getFileContents(const std::filesystem::path &path) {
  if (not std::filesystem::is_regular_file(path)) {
    throw std::runtime_error(
        fmt::format("{} is not a regular file", path.string()));
  }

  std::ifstream file(path, std::ios::in | std::ios::binary);
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  if (not file.is_open()) {
    throw std::runtime_error(
        fmt::format("Failed to open file {}", path.string()));
  }
  std::stringstream fStream;
  fStream << file.rdbuf();
  return fStream.str();
}
