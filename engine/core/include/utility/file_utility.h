#ifndef SHIROIENGINE_FILE_UTILITY_H
#define SHIROIENGINE_FILE_UTILITY_H

#include <filesystem>
#include <types.h>
#include <fstream>

namespace shiroi::file_utility {

    size_t getFileSize(const char *path);

    size_t getFileSize(std::string &path);

    size_t getFileSize(std::filesystem::path &path);
}
#endif
