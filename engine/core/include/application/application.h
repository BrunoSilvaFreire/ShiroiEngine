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
    Event<float32> earlyUpdateEvent;
    Event<float32> lateUpdateEvent;
public:
    explicit Application(const char *appName);

    ~Application();

    GraphicsContext *getContext() const;

    const string getApplicationName() const;

    Event<float32> &getEarlyUpdateEvent();

    Event<float32> &getLateUpdateEvent();

    void run();
};

struct DamageInfo {


};
#endif