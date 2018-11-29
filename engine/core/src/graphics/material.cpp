#include <graphics/material.h>

const Material Material::INVALID = Material(static_cast<uint32>(0));

uint32 Material::getShaderId() const {
    return shaderId;
}

Material::Material(uint32 shaderId) : shaderId(shaderId) {}

Material::Material(ShaderProgram *shaderId) : shaderId(shaderId->getProgramID()) {}
