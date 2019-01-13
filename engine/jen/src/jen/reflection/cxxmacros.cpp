#include <jen/reflection/cxxmacros.h>

namespace shiroi::jen::reflection {
    CXXMacroExpansion::CXXMacroExpansion(const std::string &name, const std::vector<std::string> &parameters)
            : CXXIdentifiable(name), parameters(parameters) {}
}