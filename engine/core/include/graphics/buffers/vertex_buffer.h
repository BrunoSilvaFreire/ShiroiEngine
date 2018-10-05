#ifndef SHIROIENGINE_VERTEX_BUFFER_H
#define SHIROIENGINE_VERTEX_BUFFER_H

#include <vector>
#include "opengl_buffer.h"

struct VertexLayoutElement {
private:
    uint32 type;
    uint8 count;
    bool normalized;
public:
    static uint32 getTypeSize(uint32 type) {
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

    VertexLayoutElement(uint32 type, uint8 count, bool normalized) : type(type), count(count), normalized(normalized) {
    }

    uint32 getType() const {
        return type;
    }

    uint8 getCount() const {
        return count;
    }

    bool isNormalized() const {
        return normalized;
    }

    uint32 size() {
        return count * getTypeSize(type);
    }
};

class VertexLayout {
private:
    std::vector<VertexLayoutElement> elements;
    uint16 stride = 0;
public:
    template<typename T>
    void push(uint8 amount) {
        LOG(ERROR) << "You are only allowed to push float32, uint8, uint32";
    }

    VertexLayoutElement &operator[](uint32 index) {
        return elements[index];
    }

    uint16 getStride() const {
        return stride;
    }

    size_t size() {
        return elements.size();
    }
};
template<>
void VertexLayout::push<float32>(uint8 amount) {
    elements.emplace_back(GL_FLOAT, amount, false);
    stride += amount * sizeof(float32);
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

class VertexBuffer : IGLBuffer {
public:
    explicit VertexBuffer(int32 size, void *data) : IGLBuffer(GL_ARRAY_BUFFER, size, data) {

    }

    void bind() override {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    }

    void unbind() override {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0))
    }
};

#endif