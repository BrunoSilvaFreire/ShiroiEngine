#ifndef SHIROIENGINE_MATERIAL_H
#define SHIROIENGINE_MATERIAL_H

#include <types.h>
#include <vector>

template<typename T>
struct MaterialProperty {
private:
    string name;
    T value;
public:
    MaterialProperty(const char *name, T value) : name(name), value(value) {}

    const char *getName() const {
        return name;
    }

    T getValue() const {
        return value;
    }
};

class Material {
private:
    uint32 shaderId;
    std::vector<MaterialProperty<float32 >> floatProperties;
    std::vector<MaterialProperty<uint32 >> uintProperties;
public:
    uint32 getShaderId() const {
        return shaderId;
    }
};

#endif
