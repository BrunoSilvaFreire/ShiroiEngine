#ifndef SHIROIENGINE_GRAPHIC_UTILITIES_H
#define SHIROIENGINE_GRAPHIC_UTILITIES_H

#include <glog/logging.h>
#include <GL/glew.h>
#include <types.h>

void glClearErrors();

void glCheckErrors(string functionName);

void glPrintBoundTargets() ;

#define glCall(x) glClearErrors();\
                  x;\
                  glCheckErrors(#x);

#define glDeclare(var, x)  glClearErrors();\
                  auto var = x;\
                  glCheckErrors(#x);

#endif
