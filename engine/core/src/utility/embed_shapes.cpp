#include <utility/embed_shapes.h>
#include <iostream>

inline VertexLayout createSimpleLayout(uint8 components);

const VertexLayout EmbedShapes::k3DEmbedLayout = createSimpleLayout(3);
const VertexLayout EmbedShapes::k2DEmbedLayout = createSimpleLayout(2);

VertexLayout createSimpleLayout(uint8 components) {
    VertexLayout l;
    // Position element
    l.push<float32>(components);
    return l;
}

const glm::vec3 EmbedShapes::kCubeVertices[8] = {
        glm::vec3(.5F, -.5F, .5F),
        glm::vec3(-.5F, -.5F, .5F),
        glm::vec3(.5F, -.5F, -.5F),
        glm::vec3(-.5F, -.5F, -.5F),
        glm::vec3(.5F, .5F, .5F),
        glm::vec3(-.5F, .5F, .5F),
        glm::vec3(.5F, .5F, -.5F),
        glm::vec3(-.5F, .5F, -.5F)
};
const uint32 EmbedShapes::kCubeIndices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
};
const Mesh EmbedShapes::kCube = Mesh(
        EmbedShapes::k3DEmbedLayout,
        (void *) EmbedShapes::kCubeVertices,
        8,
        std::vector<uint16>(EmbedShapes::kCubeIndices, EmbedShapes::kCubeIndices + 36)
);

const glm::vec2 EmbedShapes::kQuadVertices[4] = {
        glm::vec2(0.5, 0.5),
        glm::vec2(0.5, -0.5),
        glm::vec2(-0.5, -0.5),
        glm::vec2(-0.5, 0.5)
};

const uint32 EmbedShapes::kQuadIndices[]{
        0, 1, 2, 2, 3, 0
};
const Mesh EmbedShapes::kQuad = Mesh(
        EmbedShapes::k2DEmbedLayout,
        (void *) EmbedShapes::kQuadVertices,
        4,
        std::vector<uint16>(EmbedShapes::kQuadIndices, EmbedShapes::kQuadIndices + 6)
);