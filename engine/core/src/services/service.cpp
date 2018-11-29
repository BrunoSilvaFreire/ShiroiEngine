#include <services/service.h>

const StepFunction &RuntimeService::getMainStep() const {
    return mainStep;
}
