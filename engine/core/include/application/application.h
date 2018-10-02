#ifndef SHIROIENGINE_APPLICATION_H
#define SHIROIENGINE_APPLICATION_H

#include <types.h>
#include <glog/logging.h>
#include <graphics/graphics_context.h>
#include <utility/event.h>

class Application {
private:
    string applicationName;
    GraphicsContext *context;
    Event<float32> tickEvent;
    Event<GraphicsContext *, GLFWwindow *> renderEvent;
public:
    explicit Application(const char *appName);

    ~Application();

    GraphicsContext *getContext() const;

    Event<float32> &getTickEvent();

    Event<GraphicsContext *, GLFWwindow *> &getRenderEvent();

    const string getApplicationName() const;

    void run();
};

struct DamageInfo {


};

class Entity {
private:
    Event<DamageInfo, Entity> onDamaged;
public:
    const Event<DamageInfo, Entity> &getOnDamaged() const;
};

class EntityHealthBar {
};

#endif