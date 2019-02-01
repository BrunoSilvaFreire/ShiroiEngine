#ifndef SHIROIENGINE_APPLICATION_H
#define SHIROIENGINE_APPLICATION_H

#include <types.h>
#include <glog/logging.h>
#include <graphics/graphics_context.h>
#include <utility/event.h>
#include <utility/step_function.h>
#include <services/service_manager.h>

class Application {
private:
    c_string applicationName;
    GraphicsContext *context;
    StepFunction mainStepFunction;
    ServiceManager *serviceManager;
public:
    explicit Application(const char *appName);

    ~Application();

    GraphicsContext *getContext() const;

    const c_string getApplicationName() const;

    StepFunction &getMainStepFunction();

    void run();

    ServiceManager *getServiceManager() const;
};

struct DamageInfo {


};
#endif