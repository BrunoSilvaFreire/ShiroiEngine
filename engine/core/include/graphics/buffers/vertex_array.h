#ifndef SHIROIENGINE_VERTEX_ARARY_H
#define SHIROIENGINE_VERTEX_ARARY_H

#include "opengl_buffer.h"
#include "vertex_buffer.h"

class VertexArray : IGLBindable {
private:
    uint32 id;
    uint32 size;
public:
    VertexArray(uint32 size = 1) : id(0), size(size) {
        glCall(glGenVertexArrays(size, &id));
    }

    ~VertexArray() {
        glCall(glDeleteVertexArrays(size, &id));
    }

    void bind() override {
        glCall(glBindVertexArray(id));
    }

    void unbind() override {
        glCall(glBindVertexArray(0));
    }

    void addLayout(VertexLayout layout, VertexBuffer &buffer) {
        bind();
        buffer.bind();
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
};

#endif
