#include <jen/utility/clang_utility.h>

CXSourceRange shiroi::jen::clang_utility::getFileRange(const CXTranslationUnit &tu, std::filesystem::path filename) {
    CXFile file = clang_getFile(tu, filename.string().c_str());
    //TODO: Fix type sizes
    auto fileSize = static_cast<uint32>(shiroi::file_utility::getFileSize(filename));
    CXSourceLocation topLoc = clang_getLocationForOffset(tu, file, 0);
    CXSourceLocation lastLoc = clang_getLocationForOffset(tu, file, fileSize);
    CXSourceRange range = clang_getRange(topLoc, lastLoc);
    return range;
}
