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

shiroi::jen::GenerationParams::GenerationParams(
        shiroi::jen::GeneratedSources *sources,
        std::vector<shiroi::jen::IGenerator *> *generators
) : sources(sources), generators(generators) {

}

shiroi::jen::GeneratedSources *shiroi::jen::GenerationParams::getSources() const {
    return sources;
}

std::vector<shiroi::jen::IGenerator *> *shiroi::jen::GenerationParams::getGenerators() const {
    return generators;
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
                                      nullptr, 0, TRANSLATION_FLAGS);
    if (unit == nullptr) {
        throw std::runtime_error("Unable to create Translation Unit");
    }
    auto range = shiroi::jen::clang_utility::getFileRange(unit, filePath);
    clang_tokenize(unit, range, &tokenPtr, &totalTokens);
    auto begin = generators->begin();
    auto end = generators->end();
    for (auto it = begin; begin != end; begin++) {
        LOG(INFO) << "Processing yay";
        (*it)->process(this);
    }
}

CXChildVisitResult shiroi::jen::GeneratedSources::cursorFinder(
        CXCursor cursor,
        CXCursor parent,
        CXClientData client_data
) {
    auto *search = (CursorSearch *) client_data;
    auto cursorName = clang_getCString(clang_getCursorSpelling(cursor));
    auto tokenName = clang_getCString(clang_getTokenSpelling(search->getUnit(), search->getToken()));
    if (std::strcmp(cursorName, tokenName) == 0) {
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
