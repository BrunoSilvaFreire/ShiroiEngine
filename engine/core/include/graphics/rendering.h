#ifndef SHIROIENGINE_RENDERING_H
#define SHIROIENGINE_RENDERING_H

#include <types.h>
#include <glm/glm.hpp>

interface IDrawable {
    virtual void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
};

#endif
