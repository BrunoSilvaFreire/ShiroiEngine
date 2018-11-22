#ifndef SHIROIENGINE_RENDERING_H
#define SHIROIENGINE_RENDERING_H

#include <types.h>
#include <glm/glm.hpp>
#include <graphics/buffers/vertex_array.h>
#include <queue>
#include <ostream>

interface IDrawable {
public:
    virtual void draw(glm::mat4 viewMatrix) = 0;
};

class Renderer {
public:
    struct QueuedDrawable {
    private:
        IDrawable *drawable;
        uint16 priority;
    public:
        QueuedDrawable(IDrawable *drawable, uint16 priority);

        uint16 getPriority() const;

        IDrawable *getDrawable() const;

        bool operator<(QueuedDrawable &other) {
            return priority < other.priority;
        }

        bool operator>(QueuedDrawable &other) {
            return priority > other.priority;
        }

        bool operator==(QueuedDrawable &other) {
            return priority == other.priority;
        }

        friend std::ostream &operator<<(std::ostream &os, const QueuedDrawable &drawable);
    };

private:
    std::vector<QueuedDrawable> drawables;
public:
    static const uint16 RENDER_QUEUE_GEOMETRY = 0;
    static const uint16 RENDER_QUEUE_TRANSPARENCY = 500;
    static const uint16 RENDER_QUEUE_UI = 1000;

    explicit Renderer();

    void enqueue(IDrawable *drawable, uint16 priority);

    void dequeue(IDrawable *drawable) {
    }

    void render(uint32 renderTarget, glm::mat4 vpMatrix) const;
};

#endif
