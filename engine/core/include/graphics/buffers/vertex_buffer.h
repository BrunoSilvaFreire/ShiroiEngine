#ifndef SHIROIENGINE_VERTEX_BUFFER_H
#define SHIROIENGINE_VERTEX_BUFFER_H

#include <vector>
#include <ostream>
#include "opengl_buffer.h"

struct VertexLayoutElement {
private:
    uint32 type;
    uint8 count;
    bool normalized;
public:
    static uint32 getTypeSize(uint32 type);


    VertexLayoutElement(uint32 type, uint8 count, bool normalized);

    uint32 getType() const;

    const string getTypeName() const;

    uint8 getCount() const;

    bool isNormalized() const;

    const uint32 size() const;

    friend std::ostream &operator<<(std::ostream &os, const VertexLayoutElement &element);

    std::string getStringFromData(uint8 *ptr);
};

class VertexLayout {
private:
    std::vector<VertexLayoutElement> elements;
    uint16 stride = 0;
public:
    template<typename T>
    void push(uint8 amount);

    VertexLayoutElement &operator[](uint32 index);

    uint16 getStride() const;

    size_t size();

    const std::vector<VertexLayoutElement> &getElements() const;

};

class VertexBuffer : IGLBuffer {
public:
    explicit VertexBuffer(int32 size, void *data);

    void bind() override;

    void unbind() override;
};

#endif