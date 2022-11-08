#ifndef FILE_H
#define FILE_H

#include <filesystem>

[[nodiscard]]
std::string getFileContents(std::filesystem::path const &path);

#endif // FILE_H
