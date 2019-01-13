#ifndef SHIROIENGINE_QUEUED_CLASS_H
#define SHIROIENGINE_QUEUED_CLASS_H

#include <glog/logging.h>
#include <string>
#include <filesystem>
#include <clang-c/Index.h>
#include <types.h>
#include <jen/utility/clang_utility.h>
#include <functional>
#include <jen/generator.h>

namespace shiroi::jen {
    class IGenerator;

    class CXXClass;

    class GenerationProcessor;

    class GenerationProcessor {
    private:
        CXIndex index;
        CXTranslationUnit clangUnit;
        CXToken *tokens;
        uint32 tokenCount;
        std::vector<CXXClass> classesToProcess;
        const std::vector<shiroi::jen::IGenerator *> generators;
    public:
        explicit GenerationProcessor(
                const std::filesystem::path &file,
                const std::vector<IGenerator *> &generators,
                const std::vector<std::string> &clangArgs = std::vector<std::string>()
        );

        typedef std::vector<std::tuple<CXXClass *, std::string>> GenerationResult;

        GenerationResult process();

        const std::vector<IGenerator *> &getGenerators() const;

        void forEachToken(std::function<void(CXToken, uint32)> action);

        void forEachToken(const CXXClass * clazz, std::function<void(CXToken, uint32)> action);

        CXCursor findCursorForToken(CXToken param);

        CXCursor findTypeRefCursorForField(uint32 i);

        const CXTranslationUnit getClangUnit() const;

        CXToken getToken(uint32 i);

        uint32 getTokenIndexFor(const CXCursor &cursor);
    };

    class CXXClass {
    private:
        CXCursor cursor;
        std::string name;
        std::vector<CXXClass> parents;
    public:
        CXXClass(const CXCursor &cursor, const std::string &name, GenerationProcessor *unit,
                 const std::vector<CXXClass> &parents);

        std::string getName() const;

        const CXCursor &getCursor() const;


        std::string generate(GenerationProcessor *processor);

        bool inherits(const CXXClass &clazz);
    };

}
#endif
