#ifndef SHIROIENGINE_CLANG_UTILITY_H
#define SHIROIENGINE_CLANG_UTILITY_H

#include <clang-c/Index.h>
#include <utility/file_utility.h>
#include <glog/logging.h>

namespace shiroi::jen::clang_utility {

    CXSourceRange getFileRange(const CXTranslationUnit &tu, std::filesystem::path filename);
}
#endif
