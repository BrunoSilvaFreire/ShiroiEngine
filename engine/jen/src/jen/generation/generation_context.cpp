#include <jen/generation/cxxgenerator.h>

namespace shiroi::jen::generation {

    void CXXGenerationContext::addScope(const GeneratedScope &scope) {
        scopes.push_back(scope);
    }

    std::ostream &operator<<(std::ostream &os, const CXXGenerationContext &context) {
        for (const GeneratedScope &scope : context.scopes) {
            os << scope.parse(0);
        }
        return os;
    }
}