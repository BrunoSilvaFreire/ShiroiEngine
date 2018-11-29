#include <graphics/buffers/vertex_buffer.h>
#include <iostream>
#include <utility/string_utility.h>

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

const std::vector<VertexLayoutElement> &VertexLayout::getElements() const {
    return elements;
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

const uint32 VertexLayoutElement::size() const {
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

const string VertexLayoutElement::getTypeName() const {
    switch (type) {
        case GL_FLOAT:
            return "float";
        case GL_UNSIGNED_INT:
            return "uint32";
        case GL_UNSIGNED_BYTE:
            return "uint8";
        default:
            return "Unknown";
    }
}

std::string VertexLayoutElement::getStringFromData(uint8 *ptr) {
    std::stringstream stream;


    stream << (uint32) count << "x " << getTypeName() << " (";
    auto tSize = getTypeSize(type);
    for (int i = 0; i < count; ++i) {
        auto pos = ptr + i * tSize;

        switch (type) {
            case GL_FLOAT:
                stream << *((float32 *) pos);
            default:
                break;
        }
        if (i != count - 1) {
            stream << ", ";
        }
    }

    stream << ") [";
    for (int j = 0; j < count; ++j) {
        stream << hex(ptr + j * tSize, ptr + (j + 1) * tSize);
        if (j != count - 1) {
            stream << ' ';
        }
    }
    stream << " @ " << reinterpret_cast<void *>(ptr) << "]";
    return stream.str();
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

std::ostream &operator<<(std::ostream &os, const VertexLayoutElement &element) {
    os << "VertexLayoutElement(type: " << element.getTypeName() << ", count: " << (uint32) element.count
       << ", size: " << element.size() << ", normalized: " << element.normalized << ")";
    return os;
}
