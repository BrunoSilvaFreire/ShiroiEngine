#ifndef SHIROIENGINE_CLANG_UTILITY_H
#define SHIROIENGINE_CLANG_UTILITY_H

#include <clang-c/Index.h>
#include <utility/file_utility.h>
#include <glog/logging.h>

std::ostream &operator<<(std::ostream &stream, const CXString &str);

std::ostream &operator<<(std::ostream &stream, const CXCursor &cursor);

namespace shiroi::jen::clang_utility {

    CXSourceRange getFileRange(const CXTranslationUnit &tu, std::filesystem::path filename);

    CXCursor findClassDeclaration(CXTranslationUnit unit, std::string cName);

    CXCursor findClassDeclarationCursorFor(CXCursor refCursor);
}
#endif
