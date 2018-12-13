#ifndef SHIROIENGINE_GENERATOR_H
#define SHIROIENGINE_GENERATOR_H

#include <clang-c/Index.h>
#include <ostream>
#include <vector>
#include <filesystem>
#include <jen/utility/clang_utility.h>
#include <functional>

std::ostream &operator<<(std::ostream &stream, const CXString &str);


namespace shiroi::jen {

    class GeneratedSources;

    class IGenerator {
    public:
        virtual void process(GeneratedSources *sources) = 0;
    };

    class GenerationParams {
    private:
        GeneratedSources *sources;
        std::vector<IGenerator *> *generators;
    public:
        GenerationParams(GeneratedSources *sources, std::vector<IGenerator *> *generators);

        GeneratedSources *getSources() const;

        std::vector<IGenerator *> *getGenerators() const;
    };

    class GeneratedSources {
    private:
        CXIndex index;
        uint32 totalTokens;
        CXToken *tokenPtr;
        CXTranslationUnit unit;
    public:
        static const auto TRANSLATION_FLAGS =
                CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_DetailedPreprocessingRecord;

        GeneratedSources(
                const std::filesystem::path &path,
                std::vector<c_string> clangArguments,
                std::vector<IGenerator *> *generators
        );

    private:
        static CXChildVisitResult cursorFinder(CXCursor cursor, CXCursor parent, CXClientData client_data);

        struct CursorSearch {
        private:
            CXToken token;
            CXCursor *found;
            CXTranslationUnit unit;
        public:
            CursorSearch(CXToken &searchId, CXTranslationUnit &unit);

            const CXToken &getToken() const;

            const CXCursor *getFound() const;

            const CXTranslationUnit getUnit() const;

            void complete(CXCursor &cursor);
        };

    public:
        const void *getIndex() const;

        uint32 getTotalTokens() const;

        CXTranslationUnit getUnit() const;

        const CXCursor *findCursorForToken(CXToken &token);

        const CXToken getToken(uint32 index) {
            return tokenPtr[index];
        }

        void forEachToken(const std::function<void(CXToken, uint32)> &f) {
            LOG(INFO) << "Total files" << totalTokens;
            for (uint32 i = 0; i < totalTokens; ++i) {
                f(tokenPtr[i], i);
            }
        }
    };


}
#endif
