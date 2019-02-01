#ifndef SHIROIENGINE_SERVICE_H
#define SHIROIENGINE_SERVICE_H

#include <utility/step_function.h>

class IService {
public:

    virtual ~IService() = default;
};

class RuntimeService : IService {
private:
    StepFunction mainStep;
public:
    const StepFunction &getMainStep() const;
};

#endif
