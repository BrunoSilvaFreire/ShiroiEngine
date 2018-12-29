#include <jen/serialization_generator.h>
#include <glog/logging.h>

constexpr char ignoredTokens[] = {
        ',',
        '(',
        ')'
};

bool isIgnoredToken(char c) {
    for (int i = 0; i < 3; ++i) {
        if (c == ignoredTokens[i]) {
            return true;
        }
    }
    return false;
}

bool isSerialized(shiroi::jen::GeneratedSources *sources, CXToken t, CXCursor cursor, uint32 tokenIndex) {
    bool valid = true;
    uint32 currentTokenIndex = tokenIndex - 1;
    auto unit = sources->getUnit();
    while (valid) {
        auto currentToken = sources->getToken(currentTokenIndex);
        auto currentTokenKind = clang_getTokenKind(currentToken);

        auto spelling = clang_getCString(clang_getTokenSpelling(unit, currentToken));
        if (currentTokenKind == CXTokenKind::CXToken_Identifier) {
            if (std::strcmp(spelling, "SERIALIZE") == 0) {
                return true;
            }
        } else {
            valid = std::any_of(std::begin(ignoredTokens), std::end(ignoredTokens), [&](char c) {
                return *spelling == c;
            });
        }

        if (currentTokenIndex == 0) {
            break;
        }
        currentTokenIndex--;

    }
    return false;
}

void shiroi::jen::SerializationGenerator::process(
        shiroi::jen::GeneratedSources *sources
) {
    auto params = std::vector<std::string>();
    params.emplace_back("SerializedObject* obj");
    auto serializationScope = shiroi::jen::GeneratedScope::method("void", "serialize", params);
    auto className = "Camera";
    auto constructorDeclaration = std::string(className) + "(Scene * scene, SerializedObject * obj) : SceneObject(scene) ";
    auto serializedFields = std::vector<std::tuple<std::string, std::string>>();
    sources->forEachToken([&](CXToken t, uint32 index) {
        auto cPtr = sources->findCursorForToken(t);
        if (cPtr == nullptr) {
            return;
        }

        auto cc = *cPtr;
        auto kind = clang_getCursorKind(cc);
        if (kind == CXCursorKind::CXCursor_FieldDecl && isSerialized(sources, t, cc, index)) {
            auto type = sources->findTypeRefCursorForField(index);
            auto fieldName = clang_getCString(clang_getCursorSpelling(cc));
            auto typeName = clang_getCString(clang_getCursorSpelling(type));
            auto line = std::string() + "obj->write<" + typeName + ">(\"" + fieldName + "\", " + fieldName + ");";
            serializationScope.addLine(line);
            serializedFields.emplace_back(fieldName, typeName);
        }
    });
    if (!serializedFields.empty()) {
        constructorDeclaration += ", \n";
        for (int i = 0; i < serializedFields.size(); ++i) {
            std::tuple<std::string, std::string> field = serializedFields[i];

            auto name = std::get<0>(field);
            auto type = std::get<1>(field);
            constructorDeclaration += std::string(name) + "(obj->extract<" + type + ">(\"" + name + "\"))";
            if (i != serializedFields.size() - 1) {
                constructorDeclaration += ", ";
            }
            constructorDeclaration += "\n";
        }
    }
    sources->addScope(GeneratedScope(constructorDeclaration));
    sources->addScope(serializationScope);
}
