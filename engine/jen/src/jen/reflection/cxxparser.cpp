#include <jen/reflection/cxxparser.h>
#include <jen/reflection/cxxmacros.h>

#define CONSUMER(x) [&](CXToken token, std::string tokenContent, CXCursor cursor, std::string cursorContent, size_t &index) { x; }


namespace shiroi::jen::reflection {
    void parseClass(
            CXCursor &classCursor,
            size_t &i,
            const std::vector<CXToken> &tokens,
            CXTranslationUnit &translationUnit
    );

    void parseEnum(
            CXCursor enumNameCursor,
            size_t &i,
            const std::vector<CXToken> &tokens,
            CXTranslationUnit &translationUnit
    );

    CXXMacroExpansion parseMacroExpansion(
            CXCursor macroNameCursor,
            size_t &i,
            const std::vector<CXToken> &tokens,
            CXTranslationUnit &translationUnit
    );

    CXXUnit parse(std::filesystem::path file, std::vector<std::filesystem::path> includeDirectories) {
        auto clangArgs = std::vector<std::string>();
        clangArgs.emplace_back("-x");
        clangArgs.emplace_back("c++");
        for (std::filesystem::path &includeDir : includeDirectories) {
            clangArgs.emplace_back("-I");
            std::string str = includeDir.string();
            clangArgs.push_back(str);
        }
        auto index = clang_createIndex(false, true);
        std::vector<c_string> finalArgs;
        for (const std::string &a : clangArgs) {
            auto copy = a.c_str();
            finalArgs.push_back(copy);
        }
        auto absFile = std::filesystem::absolute(file);
        auto str = absFile.string();
        auto path = str.c_str();
        std::string argLine;
        auto totalArgs = finalArgs.size();
        for (int i = 0; i < totalArgs; ++i) {
            auto arg = finalArgs[i];
            argLine += arg;
            if (i != totalArgs - 1) {
                argLine += ' ';
            }
        }
        CXTranslationUnit clangUnit;
        clang_parseTranslationUnit2(
                index,
                path,
                finalArgs.data(),
                finalArgs.size(),
                nullptr, 0,
                CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_DetailedPreprocessingRecord,
                &clangUnit
        );
        if (clangUnit == nullptr) {
            std::string msg = std::string("Unable to create parsing unit for file '") + path + "'.";
            LOG(ERROR) << msg;
            throw std::runtime_error(msg);
        }
        CXToken *tokenPtr;
        uint32 totalTokens;
        clang_tokenize(clangUnit, clang_utility::getFileRange(clangUnit, absFile), &tokenPtr, &totalTokens);
        std::vector<CXToken> tokens(tokenPtr, tokenPtr + totalTokens);
        std::vector<CXXClass> classes;
        for (size_t j = 0; j < tokens.size(); ++j) {
            LOG(INFO) << "Token #" << j;
            auto &token = tokens[j];
            auto cursor = clang_getCursor(clangUnit, clang_getTokenLocation(clangUnit, token));
            auto cursorKind = clang_getCursorKind(cursor);
            switch (cursorKind) {
                case CXCursorKind::CXCursor_ClassDecl:
                    parseClass(cursor, j, tokens, clangUnit);
                    break;

                default:
                    LOG(INFO) << "Unhandled cursor " << cursor;
                    break;
            }
        }
        return CXXUnit();
    }

    typedef std::function<bool(CXToken, std::string, CXCursor, std::string, size_t &)> ConsumePredicate;

    void consumeWhile(
            const CXTranslationUnit &translationUnit,
            size_t &i,
            const std::vector<CXToken> &tokens,
            const ConsumePredicate &predicate) {
        bool readingParents;
        do {
            i++;
            auto token = tokens[i];
            auto cursor = clang_getCursor(translationUnit, clang_getTokenLocation(translationUnit, token));
            auto cxStr = clang_getCursorSpelling(cursor);
            auto content = std::string(clang_getCString(cxStr));
            auto tCxStr = clang_getTokenSpelling(translationUnit, token);
            auto tokenContent = std::string(clang_getCString(tCxStr));
            clang_disposeString(cxStr);
            clang_disposeString(tCxStr);
            readingParents = predicate(token, tokenContent, cursor, content, i);
        } while (readingParents && i < tokens.size());
    }

    typedef std::function<bool(CXToken, std::string, CXCursor)> TempP;


    void parseClass(
            CXCursor &classCursor,
            size_t &i,
            const std::vector<CXToken> &tokens,
            CXTranslationUnit &translationUnit
    ) {
        std::string className = clang_getCString(clang_getCursorSpelling(classCursor));
        LOG(INFO) << "Parsing class " << className;
        CXXAccessModifier accessModifier = CXXAccessModifier::INTERNAL;
        std::vector<CXXParent> parents;

        consumeWhile(translationUnit, i, tokens,
                     [&](CXToken, std::string tokenContent, CXCursor cr, std::string, size_t &) -> bool {
                         LOG(INFO) << "Token: " << cr;
                         switch (clang_getCursorKind(cr)) {
                             case CXCursorKind::CXCursor_CXXBaseSpecifier:
                                 accessModifier = getAccessModifier(tokenContent);
                                 break;
                             case CXCursorKind::CXCursor_TypeRef:
                                 parents.emplace_back(tokenContent, accessModifier);
                                 break;
                             case CXCursor_ClassDecl:
                                 if (tokenContent == "{") {
                                     return false;
                                 }
                                 break;
                             default:
                                 break;
                         }
                         return true;
                     }
        );

        LOG(INFO) << "Parents of " << className << " (" << parents.size() << ") are: ";
        for (CXXParent &str : parents) {
            LOG(INFO) << str;
        }
        std::vector<CXXField> fields;
        std::vector<CXXMacroExpansion> activeMacros;
        std::string lastTypeRef;
        consumeWhile(translationUnit, i, tokens,
                     CONSUMER({
                                  LOG(INFO) << "Is now: " << cursor << " @ " << tokenContent;
                                  switch (clang_getCursorKind(cursor)) {
                                      case CXCursorKind::CXCursor_TypeRef:
                                          lastTypeRef = tokenContent;
                                          break;
                                      case CXCursorKind::CXCursor_CXXAccessSpecifier:
                                          if (tokenContent == ":") {
                                              break;
                                          }
                                          accessModifier = getAccessModifier(tokenContent);
                                          LOG(INFO) << "Access is now " << accessModifier << "(" << tokenContent << ")";
                                          break;
                                      case CXCursorKind::CXCursor_EnumDecl:
                                          if (tokenContent == "enum") {
                                              break;
                                          }
                                          parseEnum(cursor, index, tokens, translationUnit);
                                          break;
                                      case CXCursorKind::CXCursor_MacroExpansion:
                                          activeMacros.push_back(
                                                  parseMacroExpansion(cursor, index, tokens, translationUnit));
                                          break;
                                      case CXCursorKind::CXCursor_FieldDecl:
                                          if (tokenContent == ",") {
                                              break;
                                          }
                                          fields.emplace_back(tokenContent, accessModifier, activeMacros, lastTypeRef);
                                          activeMacros.clear();
                                          break;
                                      default:
                                          break;
                                  }
                                  return true;
                              }
                     )
        );

    }

    void parseEnum(
            CXCursor enumNameCursor,
            size_t &i,
            const std::vector<CXToken> &tokens,
            CXTranslationUnit &translationUnit
    ) {
        CXString cxEnumName = clang_getCursorSpelling(enumNameCursor);
        std::string enumName = clang_getCString(cxEnumName);
        clang_disposeString(cxEnumName);
        LOG(INFO) << "Enum Name: " << enumName;

        std::vector<CXXEnum::CXXEnumConstant> constants;
        size_t enumValue = 0;
        consumeWhile(translationUnit, i, tokens, CONSUMER(
                switch (clang_getCursorKind(cursor)) {
                    case CXCursorKind::CXCursor_EnumConstantDecl:
                        constants.emplace_back(cursorContent, enumValue);
                        enumValue++;
                        break;
                    default:
                        if (tokenContent == "}") {
                            return false;
                        }
                        break;

                }
                return true;
        ));
        LOG(INFO) << "Contants: ";
        for (CXXEnum::CXXEnumConstant &constant : constants) {
            LOG(INFO) << constant;
        }
    }

    CXXMacroExpansion parseMacroExpansion(CXCursor macroNameCursor, size_t &i, const std::vector<CXToken> &tokens,
                                          CXTranslationUnit &translationUnit) {
        CXString cxMacroName = clang_getCursorSpelling(macroNameCursor);
        std::string macroName = clang_getCString(cxMacroName);
        clang_disposeString(cxMacroName);
        LOG(INFO) << "Macro Name: " << macroName;
        std::vector<std::string> macroArguments;
        consumeWhile(translationUnit, i, tokens, CONSUMER(
                if (tokenContent == "," || tokenContent == "(") {
                    return true;
                }
                if (tokenContent == ")") {
                    return false;
                }
                macroArguments.push_back(tokenContent);
                return true;
        ));
        return CXXMacroExpansion(macroName, macroArguments);
    }
}