#include <jen/serialization_generator.h>
#include <glog/logging.h>

constexpr char ignoredTokens[] = {
        ',',
        '(',
        ')'
};

bool isSerialized(shiroi::jen::GeneratedSources *sources, CXToken t, CXCursor cursor, uint32 tokenIndex) {
    bool valid = true;
    uint32 currentTokenIndex = tokenIndex - 1;
/*    while (valid) {
        auto currentToken = sources->getToken(currentTokenIndex);
        auto currentTokenKind = clang_getTokenKind(currentToken);
        currentTokenIndex--;
        if (valid) {
            valid = currentTokenIndex >= 0;
        }
    }*/
    return false;
}

void shiroi::jen::SerializationGenerator::process(
        shiroi::jen::GeneratedSources *sources
) {
    LOG(INFO) << "Processing 2 yay";

    sources->forEachToken([&](CXToken t, uint32 index) {
        auto unit = sources->getUnit();
        auto cPtr = sources->findCursorForToken(t);
        auto tokenName = std::string(clang_getCString(clang_getTokenSpelling(unit, t)));
        tokenName += " (" + std::to_string(clang_getTokenKind(t)) + ")";
        if (cPtr == nullptr) {
            LOG(INFO) << "'" << tokenName << "' has no cursor.";
            return;
        }
        auto cc = *cPtr;
        auto kind = clang_getCursorKind(cc);
        LOG(INFO) << "'" << tokenName << "' has cursor: "
                  << clang_getCString(clang_getCursorSpelling(cc)) << " ("
                  << clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(cc))) << ")";

        if (kind == CXCursorKind::CXCursor_FieldDecl && isSerialized(sources, t, cc, index)) {

        }
    });
}
