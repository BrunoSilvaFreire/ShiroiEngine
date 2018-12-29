#ifndef SHIROIENGINE_GENERATOR_H
#define SHIROIENGINE_GENERATOR_H

#include <clang-c/Index.h>
#include <ostream>
#include <vector>
#include <filesystem>
#include <jen/utility/clang_utility.h>
#include <functional>
#include <utility/string_utility.h>

std::ostream &operator<<(std::ostream &stream, const CXString &str);


namespace shiroi::jen {

    class GeneratedSources;

    class GeneratedScope {
    private:
        std::string header;
        std::vector<GeneratedScope> children;
        std::vector<std::string> lines;
    public:
        static GeneratedScope
        method(
                const std::string &returnType,
                const std::string &name,
                const std::vector<std::string> &parameters = std::vector<std::string>()
        );

        static GeneratedScope
        constructor(
                const std::string &className,
                const std::vector<std::string> &parameters = std::vector<std::string>(),
                const std::vector<std::string> &fieldsToInitialize = std::vector<std::string>()
        );

        explicit GeneratedScope(std::string &header) : header(header), children(), lines() {}

        void addLine(std::string &str);

        void addChildren(GeneratedScope &child);

        std::string toString();
    };

    class IGenerator {
    public:
        virtual void process(GeneratedSources *sources) = 0;
    };

    class GeneratedSources {
    private:
        CXIndex index;
        uint32 totalTokens;
        CXToken *tokenPtr;
        CXTranslationUnit unit;
        std::vector<GeneratedScope> scopes;
    public:

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

        void addScope(const GeneratedScope &scope);

        void forEachToken(const std::function<void(CXToken, uint32)> &f);

        std::string toString();


        CXCursor findTypeRefCursorForField(uint32 fieldTokenIndex);
    };


}
#endif
