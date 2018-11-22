#ifndef SHIROIENGINE_DEBUG_UTILITY_H
#define SHIROIENGINE_DEBUG_UTILITY_H

#include <glog/logging.h>

#define LOG_TITLE(X) LOG(INFO) << DEBUG_TITLE(X)
#define DEBUG_TITLE(X) "----- " << X << " -----"
#endif //SHIROIENGINE_DEBUG_UTILITY_H
