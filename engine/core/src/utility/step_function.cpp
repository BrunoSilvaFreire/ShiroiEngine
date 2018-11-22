#include <utility/step_function.h>

StepFunction::StepFunction() : earlyStep(), lateStep() {
}

Event<float32> &StepFunction::getEarlyStep() {
    return earlyStep;
}

Event<float32> &StepFunction::getLateStep() {
    return lateStep;
}

void StepFunction::operator()(float32 deltaTime) {
    earlyStep(deltaTime);
    lateStep(deltaTime);
}
