#include <utility/graphic_utilities.h>

void glClearErrors() {
    while (glGetError() != GLEW_NO_ERROR);
}

void glCheckErrors(string functionName) {
    uint32 error;
    while ((error = glGetError()) != GLEW_NO_ERROR) {
        LOG(FATAL) << "Error while calling function " << functionName << ": " << error;
    }
}
