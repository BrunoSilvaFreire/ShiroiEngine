#ifndef SHIROIENGINE_EMBED_SHAPES_H
#define SHIROIENGINE_EMBED_SHAPES_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <types.h>
#include <services/service.h>
#include <graphics/mesh.h>

class EmbedShapes : public IService {
private:
    VertexLayout embedLayout3D;
    VertexLayout embedLayout2D;

    Mesh *cube;
    Mesh *quad;
    Material *embedMaterial;

    // Cube
    static glm::vec3 cubeVertices[8];
    static uint32 cubeIndices[36];
    // Quad
    static glm::vec3 quadVertices[4];
    static uint32 quadIndices[6];

public:
    EmbedShapes();

    Mesh *getCube() const;

    Mesh *getQuad() const;
};

#endif //SHIROIENGINE_EMBED_SHAPES_H
