#ifndef SHIROIENGINE_CXXMACROS_H
#define SHIROIENGINE_CXXMACROS_H

#include <jen/reflection/cxxcore.h>
#include <vector>
#include <string>

namespace shiroi::jen::reflection {
    class CXXMacroExpansion : public CXXIdentifiable {
    private:
        std::vector<std::string> parameters;
    public:
        CXXMacroExpansion(const std::string &name, const std::vector<std::string> &parameters);
    };
}
#endif