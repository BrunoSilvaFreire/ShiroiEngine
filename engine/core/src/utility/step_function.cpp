#include <utility/step_function.h>

StepFunction::StepFunction() : earlyStep(), lateStep() {
}

const Event<float32> &StepFunction::getEarlyStep() const {
    return earlyStep;
}

const Event<float32> &StepFunction::getLateStep() const {
    return lateStep;
}

void StepFunction::operator()(float32 deltaTime) {
    earlyStep(deltaTime);
    lateStep(deltaTime);
}
