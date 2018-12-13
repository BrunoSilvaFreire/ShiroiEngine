#include <utility/graphic_utilities.h>

void glClearErrors() {
    while (glGetError() != GLEW_NO_ERROR);
}


void glCheckErrors(c_string functionName) {
    uint32 error;
    while ((error = glGetError()) != GLEW_NO_ERROR) {
        LOG(FATAL) << "Error while calling function " << functionName << ": " << error;
    }
}

void glPrintBoundTarget(uint32 pName, c_string desc) {
    int result;
    glGetIntegerv(pName, &result);
    LOG(INFO) << "Target '" << desc << "' bound @ " << result;
}

void glPrintBoundTargets() {
    LOG(INFO) << "Currently bound targets are:";
    glPrintBoundTarget(GL_VERTEX_ARRAY_BUFFER_BINDING, "Vertex Array");
    glPrintBoundTarget(GL_ARRAY_BUFFER_BINDING, "Vertex Buffer");
    glPrintBoundTarget(GL_ELEMENT_ARRAY_BUFFER_BINDING, "Index Buffer");

}
