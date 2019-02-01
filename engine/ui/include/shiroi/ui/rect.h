#ifndef SHIROIENGINE_RECT_H
#define SHIROIENGINE_RECT_H

#include <glm/glm.hpp>
#include <types.h>
#include <ostream>

struct Rect {
private:
    glm::vec2 position, dimensions;
public:
    Rect(float32 x, float32 y, float32 width, float32 height) :
            position(glm::vec2(x, y)),
            dimensions(glm::vec2(width, height)) {

    }

    Rect(const glm::vec2 &position = glm::vec2(0, 0),
         const glm::vec2 &dimensions = glm::vec2(0, 0)
    ) : position(position),
        dimensions(dimensions) {}

    const glm::vec2 &getPosition() const {
        return position;
    }

    const glm::vec2 &getDimensions() const {
        return dimensions;
    }

    void setPosition(const glm::vec2 &position) {
        Rect::position = position;
    }

    void setDimensions(const glm::vec2 &dimensions) {
        Rect::dimensions = dimensions;
    }

    float32 getXMin() const {
        return position.x;
    }

    float32 getXMax() const {
        return position.x + dimensions.x;
    }

    float32 getYMin() const {
        return position.y;
    }

    float32 getYMax() const {
        return position.y + dimensions.y;
    }

    void setXMin(float32 x) {
        position.x = x;
    }

    void setXMax(float32 x) {
        dimensions.x = x - position.x;
    }

    void setYMin(float32 y) {
        position.y = y;
    }

    void setYMax(float32 y) {
        dimensions.y = y - position.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Rect &rect) {
        os << "Rect(xMin: " << rect.getXMin() << ", yMin: " << rect.getYMin() << ", xMax: " << rect.getXMax()
           << ", yMax" << rect.getYMax() << ")";
        return os;
    }
};

#endif
