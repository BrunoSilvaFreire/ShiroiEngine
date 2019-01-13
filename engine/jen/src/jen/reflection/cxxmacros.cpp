#include <jen/reflection/cxxmacros.h>

namespace shiroi::jen::reflection {
    const CXXMacroExpansion CXXMacroExpansion::kInvalidExpression = CXXMacroExpansion(
            "Invalid",
            std::vector<std::string>(),
            true
    );

    CXXMacroExpansion::CXXMacroExpansion(const std::string &name, const std::vector<std::string> &parameters,
                                         bool invalid)
            : CXXIdentifiable(name), parameters(parameters), invalid(invalid) {}

    bool CXXMacroExpansion::isInvalid() const {
        return invalid;
    }
}