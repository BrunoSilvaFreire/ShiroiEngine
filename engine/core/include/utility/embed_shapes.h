#ifndef SHIROIENGINE_EMBED_SHAPES_H
#define SHIROIENGINE_EMBED_SHAPES_H

#include <glm/vec3.hpp>
#include <types.h>
#include <graphics/mesh.h>

class EmbedShapes {
public:
    static const VertexLayout kEmbedLayout;
    static const glm::vec3 kCubeVertices[8];
    static const uint32 kCubeIndices[36];
    static const Mesh kCube;
};

#endif
