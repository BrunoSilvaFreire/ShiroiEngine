#ifndef SHIROIENGINE_RENDERING_H
#define SHIROIENGINE_RENDERING_H

#include <types.h>
#include <glm/glm.hpp>
#include <graphics/buffers/vertex_array.h>

interface IDrawable {
    virtual void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
};

class Renderer {
public:
    void render(uint32 renderTarget, glm::mat4 vpMatrix) const ;
};

#endif
