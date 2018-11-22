#ifndef SHIROIENGINE_FILE_UTILITY_H
#define SHIROIENGINE_FILE_UTILITY_H

#include <filesystem>
#include <types.h>

std::string getExecutableDirectory();

#ifdef WIN32

#include <Windows.h>
#include <graphics/mesh.h>

std::string getExecutableDirectory() {
    char result[MAX_PATH];
    auto length = GetModuleFileName(nullptr, result, MAX_PATH);
    std::string str(result, length);
    return str.substr(0, str.find_last_of("\\/"));
}

#endif
#endif
