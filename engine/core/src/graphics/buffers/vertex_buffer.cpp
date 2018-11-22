#include <graphics/buffers/vertex_buffer.h>

VertexLayoutElement &VertexLayout::operator[](uint32 index) {
    return elements[index];
}

uint16 VertexLayout::getStride() const {
    return stride;
}

template<typename T>
void VertexLayout::push(uint8 amount) {
    static_assert(false, "You are only allowed to push float32, uint8, uint32")
}


template<>
void VertexLayout::push<float32>(uint8 amount) {
    elements.emplace_back(GL_FLOAT, amount, false);
    stride += amount * sizeof(float32);
}

size_t VertexLayout::size() {
    return elements.size();
}

template<>
void VertexLayout::push<uint8>(uint8 amount) {
    elements.emplace_back(GL_UNSIGNED_BYTE, amount, false);
    stride += amount * sizeof(uint8);
}

template<>
void VertexLayout::push<uint32>(uint8 amount) {
    elements.emplace_back(GL_UNSIGNED_INT, amount, true);
    stride += amount * sizeof(uint32);
}

VertexBuffer::VertexBuffer(int32 size, void *data) : IGLBuffer(GL_ARRAY_BUFFER, size, data) {

}

void VertexBuffer::bind() {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unbind() {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
}

uint32 VertexLayoutElement::size() {
    return count * getTypeSize(type);
}

bool VertexLayoutElement::isNormalized() const {
    return normalized;
}

uint8 VertexLayoutElement::getCount() const {
    return count;
}

uint32 VertexLayoutElement::getType() const {
    return type;
}

VertexLayoutElement::VertexLayoutElement(uint32 type, uint8 count, bool normalized) : type(type), count(count),
                                                                                      normalized(normalized) {
}

uint32 VertexLayoutElement::getTypeSize(uint32 type) {
    switch (type) {
        case GL_FLOAT:
            return sizeof(float32);
        case GL_UNSIGNED_INT:
            return sizeof(uint32);
        case GL_UNSIGNED_BYTE:
            return sizeof(uint8);
        default:
            return 0;
    }
}
