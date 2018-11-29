#ifndef SHIROIENGINE_OPENGL_BUFFER_H
#define SHIROIENGINE_OPENGL_BUFFER_H

#include <types.h>
#include <GL/glew.h>
#include <utility/graphic_utilities.h>

struct IGLBindable {
public:
    virtual void bind() = 0;

    virtual void unbind() = 0;

};
struct IGLIndexable {
public:
    virtual const uint32 getID() const = 0;
};
struct IGLBuffer : IGLBindable, IGLIndexable {
protected:
    uint32 id;
    int32 size;
public:
    IGLBuffer(uint32 bufferTarget, int32 size, void *data) : id(0), size(size) {
        glCall(glCreateBuffers(1, &id));
        glCall(glBindBuffer(bufferTarget, id));
        glCall(glBufferData(bufferTarget, size, data, GL_STATIC_DRAW));
        LOG(INFO) << "Vertex created @ " << id << " for buffer " << bufferTarget;
    }

    const uint32 getID() const override {
        return id;
    }

    ~IGLBuffer() {
        glCall(glDeleteBuffers(size, &id));
    }

};

template<typename T>
class AbstractIndexBuffer : IGLBuffer {
public:
    AbstractIndexBuffer(int32 count, T *data) : IGLBuffer(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data) {}

    void bind() override {
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    }

    void unbind() override {
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
};

typedef AbstractIndexBuffer<uint32> IndexBuffer;
#endif
