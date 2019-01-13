
#ifndef SHIROIENGINE_CXXCLASS_H
#define SHIROIENGINE_CXXCLASS_H

#include <utility>
#include <vector>
#include <string>
#include <types.h>
#include <ostream>
#include <jen/reflection/cxxcore.h>
#include <jen/reflection/cxxmethod.h>
#include <jen/reflection/cxxprimitives.h>
#include <jen/reflection/cxxmacros.h>

namespace shiroi::jen::reflection {


    class CXXMember : CXXIdentifiable {
    private:
        CXXAccessModifier accessModifier;
        std::vector<CXXMacroExpansion> macros;
    public:
        CXXMember(const std::string &name, CXXAccessModifier accessModifier,
                  const std::vector<CXXMacroExpansion> &macros);

        CXXAccessModifier getAccessModifier() const;

        const std::vector<CXXMacroExpansion> &getMacros() const;
    };


    class CXXField : CXXMember {
    private:
        std::string type;
    public:
        CXXField(
                const std::string &name,
                CXXAccessModifier accessModifier,
                const std::vector<CXXMacroExpansion> &macros,
                const std::string &type
        );

        const std::string &getType() const;
    };


    struct CXXParent {
    private:
        std::string parentName;
        CXXAccessModifier accessModifier;
    public:
        CXXParent(const std::string &parentName, CXXAccessModifier accessModifier);

        friend std::ostream &operator<<(std::ostream &os, const CXXParent &parent);
    };

    class CXXClass : CXXType {
    private:
        std::vector<CXXField> fields;
        std::vector<CXXParent> parents;
    public:
    };

    std::ostream &operator<<(std::ostream &stream, CXXAccessModifier modifier);
}


#endif
