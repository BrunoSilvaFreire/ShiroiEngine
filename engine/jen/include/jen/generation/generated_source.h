
#ifndef SHIROIENGINE_GENERATED_SOURCE_H
#define SHIROIENGINE_GENERATED_SOURCE_H

#include <string>
#include <vector>
#include <types.h>

namespace shiroi::jen::generation {
    class GeneratedScope {
    public:
        enum OptionFlags {
            BRACES = 1 << 0
        };
        static const OptionFlags kDefaultOptions = OptionFlags::BRACES;
    private:

        std::string header;
        OptionFlags flags;
        std::vector<std::string> lines;
        std::vector<GeneratedScope> children;
    public:
        static GeneratedScope
        method(
                const std::string &returnType,
                const std::string &name,
                const std::vector<std::string> &params = std::vector<std::string>());

        explicit GeneratedScope(
                std::string title,
                OptionFlags flags = kDefaultOptions,
                std::vector<std::string> lines = std::vector<std::string>(),
                std::vector<GeneratedScope> children = std::vector<GeneratedScope>()
        );

        std::string parse(uint32 indentLevel = 0) const;

        void addLine(const std::string &str);

        static GeneratedScope constructor(
                const std::string &clazz,
                std::vector<std::string> parameters,
                std::vector<std::string> initializers
        );
    };
}

#endif