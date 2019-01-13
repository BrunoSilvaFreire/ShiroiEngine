#include <jen/serialization_generator.h>
#include <jen/utility/generated_scope.h>
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

bool isSerialized(shiroi::jen::GenerationProcessor *sources, CXToken t, CXCursor cursor, uint32 tokenIndex) {
    bool valid = true;
    uint32 currentTokenIndex = tokenIndex - 1;
    auto unit = sources->getClangUnit();
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


std::string shiroi::jen::SerializationGenerator::generate(shiroi::jen::GenerationProcessor *processor,
                                                          shiroi::jen::CXXClass *clazz) {
    auto params = std::vector<std::string>();
    params.emplace_back("SerializedObject* obj");
    auto serializationScope = shiroi::jen::utility::GeneratedScope::method("void", "serialize", params);
    auto className = clazz->getName();
    auto constructorDeclaration =
            std::string(className) + "(Scene * scene, SerializedObject * obj) : SceneObject(scene) ";
    auto serializedFields = std::vector<std::tuple<std::string, std::string>>();

    processor->forEachToken(clazz, [&](CXToken t, uint32 index) {
        auto cc = processor->findCursorForToken(t);
        auto kind = clang_getCursorKind(cc);
        if (kind == CXCursorKind::CXCursor_FieldDecl && isSerialized(processor, t, cc, index)) {
            auto type = processor->findTypeRefCursorForField(index);
            auto fieldName = clang_getCString(clang_getCursorSpelling(cc));
            if (std::any_of(serializedFields.begin(), serializedFields.end(), [&](std::tuple<std::string, std::string> &str) {
                return std::get<0>(str) == fieldName;
            })) {
                return;
            }
            auto typeName = clang_getCString(clang_getCursorSpelling(type));
            serializedFields.emplace_back(fieldName, typeName);
            LOG(INFO) << "Found serialized field " << fieldName << ", " << typeName;
        }
    });
    if (!serializedFields.empty()) {
        for (auto field : serializedFields) {

            auto fieldName = std::get<0>(field);
            auto typeName = std::get<1>(field);

            auto line = std::string("obj->write<") + typeName + ">(\"" + fieldName + "\", " + fieldName + ");";
            serializationScope.addLine(line);
        }
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
    } else {
        serializedFields.clear();
        return "";
    }
    serializedFields.clear();
    std::string str = shiroi::jen::utility::GeneratedScope(constructorDeclaration).parse();
    str += serializationScope.parse();
    return str;
}
