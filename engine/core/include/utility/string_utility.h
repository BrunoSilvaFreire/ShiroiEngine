//
// Created by Bruno Silva Freire on 11/22/2018.
//

#ifndef SHIROIENGINE_STRING_UTILITY_H
#define SHIROIENGINE_STRING_UTILITY_H

#include <sstream>
#include <iomanip>
#include <types.h>

template<typename TInputIter>
std::string hex(TInputIter first, TInputIter last, bool use_uppercase = true, bool insert_spaces = false) {
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

#endif //SHIROIENGINE_STRING_UTILITY_H
