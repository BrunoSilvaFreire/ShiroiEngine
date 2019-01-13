#include <utility>

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

struct ParentClassSearchTuple {
    CXCursor result;
    std::string name;

    ParentClassSearchTuple(const CXCursor &result, std::string name) : result(result), name(std::move(name)) {}

};

void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr) {
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    while (pos != std::string::npos) {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + toSearch.size());
    }
}

CXCursor shiroi::jen::clang_utility::findClassDeclarationCursorFor(CXCursor refCursor) {
    if (clang_getCursorKind(refCursor) == CXCursorKind::CXCursor_ClassDecl) {
        return refCursor;
    }
    auto name = clang_getCursorSpelling(refCursor);
    auto cName = std::string(clang_getCString(name));
    clang_disposeString(name);
    findAndReplaceAll(cName, "class ", "");

    CXTranslationUnit unit = clang_Cursor_getTranslationUnit(refCursor);
    ParentClassSearchTuple data(clang_getNullCursor(), cName);

    clang_visitChildren(
            clang_getTranslationUnitCursor(unit),
            [](CXCursor child,
               CXCursor parent,
               CXClientData cData) -> CXChildVisitResult {
                auto dataPtr = static_cast<ParentClassSearchTuple *>(cData);
                if (clang_getCursorKind(child) == CXCursorKind::CXCursor_ClassDecl) {
                    std::string n = dataPtr->name;
                    auto spelling = clang_getCursorSpelling(child);
                    auto cstr = std::string(clang_getCString(spelling));
                    clang_disposeString(spelling);
                    if (cstr.rfind(n, 0) == 0) {
                        dataPtr->result = child;
                        return CXChildVisit_Break;
                    }
                }
                return CXChildVisit_Continue;
            }, &data);
    return data.result;
}

CXCursor shiroi::jen::clang_utility::findClassDeclaration(CXTranslationUnit unit, std::string cName) {
    ParentClassSearchTuple data(clang_getNullCursor(), cName);

    clang_visitChildren(
            clang_getTranslationUnitCursor(unit),
            [](CXCursor child,
               CXCursor parent,
               CXClientData cData) -> CXChildVisitResult {
                auto dataPtr = static_cast<ParentClassSearchTuple *>(cData);
                if (clang_getCursorKind(child) == CXCursorKind::CXCursor_ClassDecl) {
                    std::string n = dataPtr->name;
                    auto spelling = clang_getCursorSpelling(child);
                    auto cstr = std::string(clang_getCString(spelling));
                    clang_disposeString(spelling);
                    if (cstr.rfind(n, 0) == 0) {
                        dataPtr->result = child;
                        return CXChildVisit_Break;
                    }
                }
                return CXChildVisit_Continue;
            }, &data);
    return data.result;
}

std::ostream &operator<<(std::ostream &stream, const CXString &str) {
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const CXCursor &cursor) {
    auto kind = clang_getCursorKind(cursor);
    stream << clang_getCursorSpelling(cursor) << '(' << clang_getCursorKindSpelling(kind)
           << ", " << kind << ')';
    return stream;
}
