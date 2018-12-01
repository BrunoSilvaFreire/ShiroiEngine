#ifndef SHIROIENGINE_MESH_H
#define SHIROIENGINE_MESH_H

#include <graphics/buffers/vertex_array.h>
#include <utility/debug_utility.h>
#include <iostream>
#include <utility/string_utility.h>
#include <graphics/material.h>

class Mesh {
private:
    VertexLayout layout;
    void *vertPtr;
    uint32 totalVertices;
    std::vector<uint32> indices;
    Material *material;
public:
    Material *getMaterial() const;

    Mesh(const VertexLayout &layout, void *vertPtr, uint32 totalVertices, const std::vector<uint32> &indices,
         Material *mat);

    void exportMesh(VertexArray **vaoPtr, VertexBuffer **vboPtr, IndexBuffer **iboPtr);

    const VertexLayout &getLayout() const;

    void *getVertPtr() const;

    uint32 getTotalVertices() const;

    const std::vector<uint32> &getIndices() const;

    void printInfo();

};
#endif //SHIROIENGINE_MESH_H
