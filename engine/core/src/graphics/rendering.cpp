//
// Created by Bruno Silva Freire on 10/11/2018.
//
#define GLM_ENABLE_EXPERIMENTAL
#include <graphics/rendering.h>
#include <glm/gtx/string_cast.hpp>

void Renderer::render(uint32 renderTarget, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const {
    for (const QueuedDrawable &d : drawables) {
        d.getDrawable()->draw(viewMatrix, projectionMatrix);
    }
}

Renderer::Renderer() : drawables() {
}

void Renderer::enqueue(IDrawable *drawable, uint16 priority) {
    drawables.emplace_back(drawable, priority);
    std::sort(drawables.begin(), drawables.end());
}

uint16 Renderer::QueuedDrawable::getPriority() const {
    return priority;
}

IDrawable *Renderer::QueuedDrawable::getDrawable() const {
    return drawable;
}

Renderer::QueuedDrawable::QueuedDrawable(IDrawable *drawable, uint16 priority) : drawable(drawable),
                                                                                 priority(priority) {}

std::ostream &operator<<(std::ostream &os, const Renderer::QueuedDrawable &drawable) {
    os << "QueuedDrawable(drawable: " << drawable.drawable << ", priority: " << drawable.priority << ')';
    return os;
}
