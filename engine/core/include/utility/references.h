#ifndef SHIROIENGINE_REFERENCES_H
#define SHIROIENGINE_REFERENCES_H

#include <scenes/scene.h>

template<typename T>
struct Reference {
private:
    UUID objectId;
    T *cachedValue;
public:
    T *operator()(Scene &scene) {
        if (cachedValue != nullptr) {
            return cachedValue;
        }
        for (auto obj : scene.getObjects()) {
            if (obj->getUniqueId() == objectId) {
                return obj;
            }
        }
        return nullptr;
    }
};

#endif
