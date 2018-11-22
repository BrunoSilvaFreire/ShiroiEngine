#ifndef SHIROIENGINE_MESH_H
#define SHIROIENGINE_MESH_H

#include <graphics/buffers/vertex_array.h>

class Mesh {
private:
    VertexLayout layout;
    void *vertPtr;
    uint32 totalVertices;
    std::vector<uint16> indices;
public:
    Mesh(const VertexLayout &layout, void *vertPtr, uint32 totalVertices, const std::vector<uint16> &indices) : layout(
            layout), vertPtr(vertPtr), totalVertices(totalVertices), indices(indices) {}

    void exportMesh(VertexArray *vao, VertexBuffer *vbo, IndexBuffer *ibo) {
        *vao = VertexArray();
        auto tVBO = VertexBuffer(totalVertices * layout.getStride(), vertPtr);
        *vbo = tVBO;
        *ibo = IndexBuffer(indices.size(), indices.data());
        vao->addLayout(layout, tVBO);
    }
};

#endif //SHIROIENGINE_MESH_H
