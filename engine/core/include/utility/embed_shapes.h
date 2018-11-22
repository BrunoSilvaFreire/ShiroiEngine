#ifndef SHIROIENGINE_EMBED_SHAPES_H
#define SHIROIENGINE_EMBED_SHAPES_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <types.h>
#include <graphics/mesh.h>

class EmbedShapes {
public:
    static const VertexLayout k3DEmbedLayout;
    static const VertexLayout k2DEmbedLayout;
    // Cube
    static const glm::vec3 kCubeVertices[8];
    static const uint32 kCubeIndices[36];
    static const Mesh kCube;
    // Quad
    static const glm::vec2 kQuadVertices[4];
    static const uint32 kQuadIndices[6];
    static const Mesh kQuad;
};

#endif
