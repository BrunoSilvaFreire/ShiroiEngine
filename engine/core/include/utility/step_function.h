#ifndef SHIROIENGINE_STEP_FUNCTION_H
#define SHIROIENGINE_STEP_FUNCTION_H

#include <utility/event.h>
#include <types.h>

class StepFunction {
private:
    Event<float32> earlyStep;
    Event<float32> lateStep;
public:
    StepFunction();

    const Event<float32> &getEarlyStep() const;

    const Event<float32> &getLateStep() const;

    void operator()(float32 deltaTime);
};

#endif