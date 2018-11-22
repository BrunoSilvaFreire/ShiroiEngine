#include <graphics/buffers/vertex_array.h>


void VertexArray::unbind() {
    glCall(glBindVertexArray(0));
}

void VertexArray::addLayout(VertexLayout &layout, VertexBuffer &buffer) {
    LOG(INFO) << "Bingind self";
    bind();
    LOG(INFO) << "Bingind buffer";
    buffer.bind();
    LOG(INFO) << "Bingind Getting stride";
    auto stride = layout.getStride();
    uint32 offset = 0;
    for (uint32 i = 0; i < layout.size(); ++i) {
        auto element = layout[i];
        glCall(glEnableVertexAttribArray(i));
        LOG(INFO) << "Enabling vertex attri #" << i;
        LOG(INFO) << element.getCount() << ", " << element.getType() << ", " << element.isNormalized()
                  << ", stride: "
                  << stride;
        glCall(glVertexAttribPointer(i, element.getCount(), element.getType(),
                                     (GLboolean) element.isNormalized(), stride,
                                     reinterpret_cast<const void *>(offset)));
        offset += element.size();

    }
}

const uint32 VertexArray::getID() const {
    return id;
}

VertexArray::VertexArray(uint32 size) : id(0), size(size) {
    glCall(glGenVertexArrays(size, &id));
}

VertexArray::~VertexArray() {
    glCall(glDeleteVertexArrays(size, &id));
}

void VertexArray::bind() {
    LOG(INFO) << "Binding VAO @ " << id;
    glCall(glBindVertexArray(id));
}
