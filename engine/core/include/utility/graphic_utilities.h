#ifndef SHIROIENGINE_GRAPHIC_UTILITIES_H
#define SHIROIENGINE_GRAPHIC_UTILITIES_H

#include <glog/logging.h>
#include <GL/glew.h>
#include <types.h>

void glClearErrors();

void glCheckErrors(string functionName);


#define glCall(x) glClearErrors();\
                  x;\
                  glCheckErrors(#x);

#endif
