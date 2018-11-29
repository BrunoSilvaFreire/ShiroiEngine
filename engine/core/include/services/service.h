#ifndef SHIROIENGINE_SERVICE_H
#define SHIROIENGINE_SERVICE_H

#include <utility/step_function.h>

class Service {
public:
    virtual ~Service() = default;
};

class RuntimeService : Service {
private:
    StepFunction mainStep;
public:
    const StepFunction &getMainStep() const;
};

#endif
