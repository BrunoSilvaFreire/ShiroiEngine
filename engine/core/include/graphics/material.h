#ifndef SHIROIENGINE_MATERIAL_H
#define SHIROIENGINE_MATERIAL_H

#include <types.h>
#include <vector>
#include <graphics/shaders/shader_program.h>

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
    static const Material INVALID;

    Material(uint32 shaderId);

    Material(ShaderProgram *shaderId);

    uint32 getShaderId() const;
};

#endif
