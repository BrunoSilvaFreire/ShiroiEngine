#ifndef SHIROIENGINE_GRAPHIC_UTILITIES_H
#define SHIROIENGINE_GRAPHIC_UTILITIES_H

#include <glog/logging.h>
#include <GL/glew.h>
#include <types.h>

void glClearErrors() {
    while (glGetError() != GLEW_NO_ERROR);
}

void glCheckErrors(string functionName) {
    uint32 error;
    while ((error = glGetError()) != GLEW_NO_ERROR) {
        LOG(FATAL) << "Error while calling function " << functionName << ": " << error;
    }
}


#define glCall(x) glClearErrors();\
                  x;\
                  glCheckErrors(#x);

#endif
