#ifndef SHIROIENGINE_COLLECTION_UTILITIES_H
#define SHIROIENGINE_COLLECTION_UTILITIES_H

#include <vector>

template<typename T, typename C>
T *firstOf(std::vector<C> collection) {
    for (C i : collection) {
        auto found = dynamic_cast<T *>(i);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

#endif
