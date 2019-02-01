#ifndef SHIROIENGINE_DOCK_H
#define SHIROIENGINE_DOCK_H

#include <shiroi/ui/rect.h>
#include <application/application.h>

enum DockingDirection {
    Left,
    Right,
    Up,
    Down
};

class Dock;

class ContentHost {
private:
    std::vector<const Dock *> contained;
public:
    virtual Rect getRect() = 0;

    ContentHost() : contained() {

    }

    void addChild(const Dock *dock) {
        contained.push_back(dock);
    }

    void removeChild(const Dock *dock) {
        contained.erase(std::remove(contained.begin(), contained.end(), dock), contained.end());
    }

    virtual const Application *getApplication() const = 0;

    void draw(const glm::mat4 &vpMatrix) {
        Rect r = getRect();
        glm::vec4 min(r.getXMin(), r.getYMin(), 0, 1);
        glm::vec4 max(r.getXMax(), r.getYMax(), 0, 1);
        min = vpMatrix * min;
        max = vpMatrix * max;

        LOG(INFO) << "Rect @ " << r;

        glColor3i(127, 127, 0);
        glRectf(min.x, min.y, max.x, max.y);
    }
};

class WindowHost : public ContentHost {
private:
    Application *app;
public:
    explicit WindowHost(Application *app) : app(app) {
    }

    const Application *getApplication() const override {
        return app;
    }

    Rect getRect() override {
        GraphicsContext *context = app->getContext();
        int32 width, height;
        glfwGetWindowSize(context->getWindow(), &width, &height);
        return Rect(0, 0, width, height);
    }


};


class Dock : ContentHost {
private:
    ContentHost *parent;
    DockingDirection direction;
    float32 distance;

public:
    Dock(
            ContentHost *parent,
            DockingDirection direction,
            float32 distance
    ) : parent(parent), direction(direction), distance(distance) {
        Dock::parent->addChild(this);
    }

    ~Dock() {
        parent->removeChild(this);
    }

    Rect getRect() override {
        Rect r = parent->getRect();
        switch (direction) {
            case Left:
                r.setXMax(r.getXMin() + distance);
                break;
            case Right:
                r.setXMin(r.getXMax() - distance);
                break;
            case Up:
                r.setYMin(r.getYMax() - distance);
                break;
            case Down:
                r.setYMax(r.getYMin() + distance);
                break;
        }
        return r;
    }

    const Application *getApplication() const override {
        return parent->getApplication();
    }


};

#endif
