#include <graphics/buffers/vertex_array.h>


void VertexArray::unbind() {
    glCall(glBindVertexArray(0));
}

void VertexArray::addLayout(VertexLayout &layout, VertexBuffer &buffer) {
    bind();
    buffer.bind();
    auto stride = layout.getStride();
    uint32 offset = 0;
    for (uint32 i = 0; i < layout.size(); ++i) {
        auto element = layout[i];
        glCall(glEnableVertexAttribArray(i));
        LOG(INFO) << "Enabling vertex attribute #" << i;
        LOG(INFO) << element;
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
    glCall(glBindVertexArray(id));
}
