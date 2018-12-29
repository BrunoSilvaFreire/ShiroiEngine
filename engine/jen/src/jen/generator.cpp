#include <glog/logging.h>
#include <clang-c/Index.h>
#include <utility/file_utility.h>

#include <jen/generator.h>
#include <jen/utility/clang_utility.h>

std::ostream &operator<<(std::ostream &stream, const CXString &str) {
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

shiroi::jen::GeneratedSources::GeneratedSources(
        const std::filesystem::path &path,
        std::vector<c_string> clangArguments,
        std::vector<shiroi::jen::IGenerator *> *generators
) : totalTokens(0), tokenPtr(nullptr), unit(nullptr) {
    index = clang_createIndex(false, true);
    std::filesystem::path filePath = std::filesystem::absolute(path);
    auto str = filePath.string();
    const char *filename = str.c_str();
    LOG(INFO) << "Generating translation unit";

    unit = clang_parseTranslationUnit(index, filename, clangArguments.data(), clangArguments.size(),
                                      nullptr, 0, CXTranslationUnit_DetailedPreprocessingRecord);
    if (unit == nullptr) {
        throw std::runtime_error("Unable to create Translation Unit");
    }
    auto range = shiroi::jen::clang_utility::getFileRange(unit, filePath);
    clang_tokenize(unit, range, &tokenPtr, &totalTokens);
    auto begin = generators->begin();
    auto end = generators->end();
    for (auto it = begin; begin != end; begin++) {
        (*it)->process(this);
    }
}

CXChildVisitResult shiroi::jen::GeneratedSources::cursorFinder(
        CXCursor cursor,
        CXCursor parent,
        CXClientData client_data
) {
    auto *search = (CursorSearch *) client_data;
    auto unit = search->getUnit();
    auto token = search->getToken();
    auto cloc = clang_getCursorLocation(cursor);
    auto tloc = clang_getTokenLocation(unit, token);
    if (clang_equalLocations(cloc, tloc)) {
        search->complete(cursor);
        return CXChildVisit_Break;
    }
    return CXChildVisit_Recurse;
}

const CXCursor *shiroi::jen::GeneratedSources::findCursorForToken(CXToken &token) {
    CursorSearch search(token, unit);
    auto unitCursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(unitCursor, &cursorFinder, &search);
    return search.getFound();
}

const void *shiroi::jen::GeneratedSources::getIndex() const {
    return index;
}

uint32 shiroi::jen::GeneratedSources::getTotalTokens() const {
    return totalTokens;
}

CXTranslationUnit shiroi::jen::GeneratedSources::getUnit() const {
    return unit;
}

void shiroi::jen::GeneratedSources::forEachToken(const std::function<void(CXToken, uint32)> &f) {
    for (uint32 i = 0; i < totalTokens; ++i) {
        f(tokenPtr[i], i);
    }
}

void shiroi::jen::GeneratedSources::addScope(const shiroi::jen::GeneratedScope &scope) {
    scopes.push_back(scope);
}

std::string shiroi::jen::GeneratedSources::toString() {
    std::string result;
    for (auto &s : scopes) {
        result += s.toString();
    }
    return result;
}

CXCursor shiroi::jen::GeneratedSources::findTypeRefCursorForField(uint32 fieldTokenIndex) {
    for (uint32 i = fieldTokenIndex - 1; i >= 0; i--) {
        auto token = tokenPtr[i];
        auto cursor = findCursorForToken(token);
        if (cursor != nullptr) {
            auto c = *cursor;
            if (clang_getCursorKind(c) == CXCursorKind::CXCursor_TypeRef) {
                return c;
            }
        }
    }
    throw std::runtime_error("Couldn't find field!");
}


shiroi::jen::GeneratedSources::CursorSearch::CursorSearch(CXToken &searchId, CXTranslationUnit &unit) : token(searchId),
                                                                                                        found(),
                                                                                                        unit(unit) {
}

const CXToken &shiroi::jen::GeneratedSources::CursorSearch::getToken() const {
    return token;
}

const CXCursor *shiroi::jen::GeneratedSources::CursorSearch::getFound() const {
    return found;
}

const CXTranslationUnit shiroi::jen::GeneratedSources::CursorSearch::getUnit() const {
    return unit;
}

void shiroi::jen::GeneratedSources::CursorSearch::complete(CXCursor &cursor) {
    found = new CXCursor(cursor);
}

std::string shiroi::jen::GeneratedScope::toString() {
    std::string result = header;
    result += " {\n";
    for (auto &line: lines) {
        result += "    ";
        result += line;
        result += "\n";
    }
    for (GeneratedScope &child : children) {
        result += child.toString();
        result += "\n";
    }
    result += "}\n";
    return result;
}

void shiroi::jen::GeneratedScope::addChildren(shiroi::jen::GeneratedScope &child) {
    children.push_back(child);
}

void shiroi::jen::GeneratedScope::addLine(std::string &str) {
    lines.push_back(str);
}

shiroi::jen::GeneratedScope shiroi::jen::GeneratedScope::method(
        const std::string &returnType,
        const std::string &name,
        const std::vector<std::string> &parameters
) {
    auto hdr = returnType + " " + name + "(" + shiroi::string_utility::join(parameters, ", ") + ")";
    return GeneratedScope(hdr);
}

shiroi::jen::GeneratedScope
shiroi::jen::GeneratedScope::constructor(
        const std::string &className,
        const std::vector<std::string> &parameters,
        const std::vector<std::string> &fieldsToInitialize
) {
    auto hdr = className + "(" + shiroi::string_utility::join(parameters) + ")";
    if (!fieldsToInitialize.empty()) {
        hdr += shiroi::string_utility::join(fieldsToInitialize, ", ", [](std::string v) -> std::string {
            return v + "(" + v + ")";
        });
    }
    return shiroi::jen::GeneratedScope(hdr);
}
