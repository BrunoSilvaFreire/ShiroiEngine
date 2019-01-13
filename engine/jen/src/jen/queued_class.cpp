#include <jen/queued_class.h>
#include <functional>

namespace shiroi::jen {

    std::string CXXClass::getName() const {
        return name;
    }

    CXXClass::CXXClass(
            const CXCursor &cursor,
            const std::string &name,
            GenerationProcessor *unit,
            const std::vector<CXXClass> &parents
    ) : cursor(cursor), name(name), parents(parents) {

    }

    std::string CXXClass::generate(GenerationProcessor *processor) {
        std::string result;
        for (IGenerator *generator : processor->getGenerators()) {
            result += generator->generate(processor, this);
        }
        return result;
    }

    const CXCursor &CXXClass::getCursor() const {
        return cursor;
    }

    bool CXXClass::inherits(const CXXClass &clazz) {
        if (clazz.name == name) {
            return true;
        }
        for (CXXClass &parent : parents) {
            if (parent.inherits(clazz)) {
                return true;
            }
        }
        return false;
    }

    struct ClassParseTuple {
        std::vector<CXXClass> &children;
        GenerationProcessor *processor;
    };

    CXXClass parseClass(CXCursor cursor, GenerationProcessor *processor) {

        auto className = clang_getCursorSpelling(cursor);
        auto name = std::string(clang_getCString(className));
        clang_disposeString(className);
        std::vector<CXXClass> children;
        ClassParseTuple data{children, processor};
        clang_visitChildren(cursor,
                            [](CXCursor child, CXCursor parent,
                               CXClientData client_data_2) -> CXChildVisitResult {
                                bool isChild = clang_getCursorKind(child) ==
                                               CXCursorKind::CXCursor_CXXBaseSpecifier;
                                if (isChild) {
                                    auto c = static_cast<ClassParseTuple *>(client_data_2);
                                    auto childClassDecl = clang_utility::findClassDeclarationCursorFor(child);
                                    if (clang_getCursorKind(childClassDecl) == CXCursorKind::CXCursor_ClassDecl) {
                                        c->children.push_back(parseClass(childClassDecl, c->processor));
                                    }
                                }
                                return isChild ? CXChildVisit_Continue : CXChildVisit_Break;
                            }, &data
        );
        return CXXClass(cursor, name, processor, children);
    }

    GenerationProcessor::GenerationProcessor(
            const std::filesystem::path &file,
            const std::vector<IGenerator *> &generators,
            const std::vector<std::string> &clangArgs
    ) : index(nullptr),
        clangUnit(nullptr),
        tokens(nullptr),
        tokenCount(0),
        classesToProcess(),
        generators(generators) {

        index = clang_createIndex(false, true);
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
        auto code = clang_parseTranslationUnit2(
                index,
                path,
                finalArgs.data(),
                finalArgs.size(),
                nullptr, 0,
                CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_DetailedPreprocessingRecord,
                &clangUnit
        );
        if (clangUnit == nullptr) {
            LOG(ERROR) << "Unable to create parsing unit for file '" << path << "'. Return code: " << code;
            return;
        }
        auto range = clang_utility::getFileRange(clangUnit, absFile);
        clang_tokenize(clangUnit, range, &tokens, &tokenCount);
        clang_visitChildren(
                clang_getTranslationUnitCursor(clangUnit),
                [](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
                    auto ptr = static_cast<GenerationProcessor *>(client_data);

                    if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_ClassDecl) {

                        ptr->classesToProcess.push_back(parseClass(cursor, ptr));
                    }
                    return CXChildVisit_Recurse;
                }, this
        );
        if (classesToProcess.empty()) {
            LOG(INFO) << "There are no classes to process";
        }

    }

    GenerationProcessor::GenerationResult GenerationProcessor::process() {
        GenerationResult result;
        for (CXXClass &clazz : classesToProcess) {
            auto content = clazz.generate(this);
            result.emplace_back(&clazz, content);
        }
        return result;
    }

    const std::vector<IGenerator *> &GenerationProcessor::getGenerators() const {
        return generators;
    }

    void GenerationProcessor::forEachToken(std::function<void(CXToken, uint32)> action) {
        for (uint32 i = 0; i < tokenCount; ++i) {
            action(tokens[i], i);
        }
    }

    void GenerationProcessor::forEachToken(const CXXClass *clazz, std::function<void(CXToken, uint32)> action) {
        auto i = GenerationProcessor::getTokenIndexFor(clazz->getCursor());
        for (; i < tokenCount; i++) {
            action(tokens[i], i);
        }
    }

    CXCursor GenerationProcessor::findCursorForToken(CXToken param) {
        return clang_getCursor(clangUnit, clang_getTokenLocation(clangUnit, param));
    }

    CXCursor GenerationProcessor::findTypeRefCursorForField(uint32 i) {
        i--;
        for (; i >= 0; --i) {
            auto token = tokens[i];
            auto cursor = findCursorForToken(token);
            switch (clang_getCursorKind(cursor)) {
                case CXCursorKind::CXCursor_TypeRef:
                    return cursor;
            }
            if (i == 0) {
                break;
            }
        }
        return clang_getNullCursor();
    }

    const CXTranslationUnit GenerationProcessor::getClangUnit() const {
        return clangUnit;
    }

    CXToken GenerationProcessor::getToken(uint32 i) {
        return tokens[i];
    }

    uint32 GenerationProcessor::getTokenIndexFor(const CXCursor &cursor) {
        auto loc = clang_getCursorLocation(cursor);
        for (uint32 i = 0; i < tokenCount; i++) {
            auto tokenLoc = clang_getTokenLocation(clangUnit, tokens[i]);
            if (clang_equalLocations(loc, tokenLoc)) {
                return i;
            }
        }
        return static_cast<uint32>(-1);
    }
}
