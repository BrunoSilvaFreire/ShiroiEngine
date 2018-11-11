#ifndef SHIROIENGINE_VERTEX_ARARY_H
#define SHIROIENGINE_VERTEX_ARARY_H

#include "opengl_buffer.h"
#include "vertex_buffer.h"

class VertexArray : IGLBindable, IGLIndexable {
private:
    uint32 id;
    uint32 size;
public:
    explicit VertexArray(uint32 size = 1);

    ~VertexArray();

    void bind() override;

    void unbind() override;


    const uint32 getID() const override;

    void addLayout(VertexLayout &layout, VertexBuffer &buffer);
};

#endif
