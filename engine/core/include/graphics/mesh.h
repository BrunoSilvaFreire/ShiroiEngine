#ifndef SHIROIENGINE_MESH_H
#define SHIROIENGINE_MESH_H

#include <graphics/buffers/vertex_array.h>
#include <utility/debug_utility.h>
#include <iostream>
#include <utility/string_utility.h>

class Mesh {
private:
    VertexLayout layout;
    void *vertPtr;
    uint32 totalVertices;
    std::vector<uint16> indices;
public:
    Mesh(const VertexLayout &layout, void *vertPtr, uint32 totalVertices, const std::vector<uint16> &indices) : layout(
            layout), vertPtr(vertPtr), totalVertices(totalVertices), indices(indices) {}

    void exportMesh(VertexArray **vao, VertexBuffer **vbo, IndexBuffer **ibo) {
        *vao = new VertexArray();
        auto tVBO = new VertexBuffer(totalVertices * layout.getStride(), vertPtr);
        *vbo = tVBO;
        *ibo = new IndexBuffer(indices.size(), indices.data());
        (*vao)->addLayout(layout, *tVBO);
    }

    const VertexLayout &getLayout() const {
        return layout;
    }

    void *getVertPtr() const {
        return vertPtr;
    }

    uint32 getTotalVertices() const {
        return totalVertices;
    }

    const std::vector<uint16> &getIndices() const {
        return indices;
    }

    void printInfo() {
        LOG_TITLE("Displaying mesh information.");
        LOG_TITLE("Layout");
        auto e = layout.getElements();
        LOG(INFO) << "Total of " << e.size() << " elements.";
        for (auto element : e) {
            LOG(INFO) << element;
        }
        auto root = reinterpret_cast<uint8 *>(vertPtr);
        LOG_TITLE("Mesh Content");
        LOG(INFO) << "Begins @ " << (void *) root;
        for (uint32 i = 0; i < totalVertices; i++) {
            auto ptr = (root + i * layout.getStride());
            auto elements = layout.getElements();
            uint32 offset = 0;
            LOG(INFO) << "Vertex #" << i;
            for (int j = 0; j < elements.size(); ++j) {
                VertexLayoutElement &element = elements[j];
                auto start = ptr + offset;
                auto msg = element.getStringFromData(start);
                LOG(INFO) << "* Element #" << j << ": " << msg;
                offset += element.size();
            }
        }
        LOG_TITLE("Displayed mesh information.");
    }

};

#endif //SHIROIENGINE_MESH_H
