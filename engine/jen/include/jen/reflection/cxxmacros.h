#ifndef SHIROIENGINE_CXXMACROS_H
#define SHIROIENGINE_CXXMACROS_H

#include <jen/reflection/cxxcore.h>
#include <vector>
#include <string>

namespace shiroi::jen::reflection {
    class CXXMacroExpansion : public CXXIdentifiable {
    private:
        bool invalid;
        std::vector<std::string> parameters;
    public:
        const static CXXMacroExpansion kInvalidExpression;

        bool isInvalid() const;

        CXXMacroExpansion(const std::string &name, const std::vector<std::string> &parameters, bool invalid = false);
    };
}
#endif