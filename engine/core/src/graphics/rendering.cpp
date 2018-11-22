//
// Created by Bruno Silva Freire on 10/11/2018.
//

#include <graphics/rendering.h>

void Renderer::render(uint32 renderTarget, glm::mat4 vpMatrix) const {
    LOG(INFO) << "Yay";
    for (const QueuedDrawable &d : drawables) {
        LOG(INFO) << "Drawing " << d;
        d.getDrawable()->draw(vpMatrix);
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
