#include <utility/embed_shapes.h>
#include <iostream>

inline VertexLayout createSimpleLayout();

const VertexLayout EmbedShapes::kEmbedLayout = createSimpleLayout();

VertexLayout createSimpleLayout() {
    VertexLayout l;
    // Position element
    l.push<float32>(3);
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
const Mesh EmbedShapes::kCube = Mesh(EmbedShapes::kEmbedLayout,
                                     (void *) EmbedShapes::kCubeVertices,
                                     8,
                                     std::vector<uint16>(EmbedShapes::kCubeIndices, EmbedShapes::kCubeIndices + 7));