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

struct IGLBuffer : IGLBindable {
protected:
    uint32 id;
    int32 size;
public:
    IGLBuffer(uint32 bufferTarget, int32 size, void *data) : id(0), size(size) {


        glCall(glCreateBuffers(size, &id));
        glCall(glBindBuffer(bufferTarget, id));
        glCall(glBufferData(bufferTarget, size, data, GL_STATIC_DRAW));
    }

    ~IGLBuffer() {
        glCall(glDeleteBuffers(size, &id));
    }

};

template<typename T>
class AbstractIndexBuffer : IGLBuffer {
public:
    AbstractIndexBuffer(int32 size, T *data) : IGLBuffer(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(T), data) {}

    void bind() override {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void unbind() override {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};

typedef AbstractIndexBuffer<uint16> IndexBuffer;
#endif
