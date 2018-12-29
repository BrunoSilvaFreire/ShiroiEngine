#pragma once

#ifndef SHIROIENGINE_STRING_UTILITY_H
#define SHIROIENGINE_STRING_UTILITY_H

#include <sstream>
#include <iomanip>
#include <types.h>
#include <vector>
#include <functional>

namespace shiroi::string_utility {
    template<typename T>
    std::string hex(T first, T last, bool use_uppercase = true, bool insert_spaces = false) {
        std::ostringstream ss;
        ss << std::hex << std::setfill('0');
        if (use_uppercase)
            ss << std::uppercase;
        while (first != last) {
            ss << std::setw(2) << static_cast<int>(*first++);
            if (insert_spaces && first != last)
                ss << " ";
        }
        return ss.str();
    }

    std::vector<std::string> split(std::string strToSplit, int8 delimeter);

    std::string join(
            const std::vector<std::string> &strings,
            const std::string &separator = ", ",
            std::function<std::string(std::string)> transform = nullptr
    );

}
#endif