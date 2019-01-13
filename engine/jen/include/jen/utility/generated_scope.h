#include <utility>

#ifndef SHIROIENGINE_GENERATED_SCOPE_H
#define SHIROIENGINE_GENERATED_SCOPE_H

#include <vector>
#include <ostream>
#include <types.h>

namespace shiroi::jen::utility {
    class GeneratedScope {
    public:
        enum OptionFlags {
            BRACES = 1 << 0
        };
        static const OptionFlags kDefaultOptions = OptionFlags::BRACES;
    private:

        std::string title;
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

        std::string parse(uint32 indentLevel = 0);

        void addLine(const std::string &str);
    };
}
#endif
