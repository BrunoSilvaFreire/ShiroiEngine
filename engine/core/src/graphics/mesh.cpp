#include <graphics/mesh.h>


Mesh::Mesh(const VertexLayout &layout, void *vertPtr, uint32 totalVertices, const std::vector<uint32> &indices,
           Material *mat) : layout(
        layout), vertPtr(vertPtr), totalVertices(totalVertices), indices(indices), material(mat) {}

Material *Mesh::getMaterial() const {
    return material;
}

void Mesh::printInfo() {
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

uint32 Mesh::getTotalVertices() const {
    return totalVertices;
}

const VertexLayout &Mesh::getLayout() const {
    return layout;
}

void Mesh::exportMesh(VertexArray **vao, VertexBuffer **vbo, IndexBuffer **ibo) {
    *vao = new VertexArray();
    auto tVBO = new VertexBuffer(totalVertices * layout.getStride(), vertPtr);
    *vbo = tVBO;
    LOG(INFO) << "Using " << indices.size();
    *ibo = new IndexBuffer(indices.size(), indices.data());
    (*vao)->addLayout(layout, *tVBO);
}

void *Mesh::getVertPtr() const {
    return vertPtr;
}

const std::vector<uint32> &Mesh::getIndices() const {
    return indices;
}

