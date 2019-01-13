#ifndef SHIROIENGINE_CXXGENERATOR_H
#define SHIROIENGINE_CXXGENERATOR_H

#include <jen/reflection/cxxparser.h>
#include <jen/generation/generated_source.h>
#include <ostream>

namespace shiroi::jen::generation {
    class CXXGenerationContext {
    private:
        std::vector<GeneratedScope> scopes;
    public:
        void addScope(const GeneratedScope &scope);

        friend std::ostream &operator<<(std::ostream &os, const CXXGenerationContext &context);
    };

    std::ostream &operator<<(std::ostream &os, const CXXGenerationContext &context);


    class CXXGenerator {
    public:
        virtual void generate(
                const reflection::CXXUnit &unit,
                const reflection::CXXClass &clazz,
                CXXGenerationContext &context
        ) = 0;
    };

}
#endif
