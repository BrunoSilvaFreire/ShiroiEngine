#ifndef SHIROIENGINE_APPLICATION_H
#define SHIROIENGINE_APPLICATION_H

#include <types.h>
#include <glog/logging.h>
#include <graphics/graphics_context.h>
#include <utility/event.h>
#include <utility/step_function.h>

class Application {
private:
    string applicationName;
    GraphicsContext *context;
    StepFunction mainStepFunction;
public:
    explicit Application(const char *appName);

    ~Application();

    GraphicsContext *getContext() const;

    const string getApplicationName() const;

    StepFunction &getMainStepFunction();

    void run();
};

struct DamageInfo {


};
#endif