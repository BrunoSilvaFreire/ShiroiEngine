#include <jen/reflection/cxxclass.h>

namespace shiroi::jen::reflection {
    const std::string& CXXIdentifiable::getName() const {
        return name;
    }

    CXXIdentifiable::CXXIdentifiable(const std::string &name) : name(name) {}

    CXXType::CXXType(const std::string &name) : CXXIdentifiable(name) {}

    CXXParameter::CXXParameter(const std::string &name, CXXType *type) : CXXIdentifiable(name), type(type) {}

    CXXType *CXXParameter::getType() const {
        return type;
    }

    CXXAccessModifier CXXMember::getAccessModifier() const {
        return accessModifier;
    }


    const std::vector<CXXMacroExpansion> &CXXMember::getMacros() const {
        return macros;
    }

    CXXMember::CXXMember(const std::string &name, CXXAccessModifier accessModifier,
                         const std::vector<CXXMacroExpansion> &macros) : CXXIdentifiable(name),
                                                                         accessModifier(accessModifier),
                                                                         macros(macros) {}

    const CXXMacroExpansion &CXXMember::findMacroExpansion(const std::string &name) const {
        for (const CXXMacroExpansion &macro : macros) {
            if (macro.getName() == name) {
                return macro;
            }
        }
        return CXXMacroExpansion::kInvalidExpression;
    }

    const std::vector<CXXParameter> &CXXMethod::getParameters() const {
        return parameters;
    }

    bool CXXPrimitive::isUnsigned() const {
        return (type & CXXPrimitiveType::UNSIGNED) == CXXPrimitiveType::UNSIGNED;
    }

    CXXPrimitive::CXXPrimitiveType CXXPrimitive::getType() const {
        return type;
    }

    const CXXPrimitive CXXPrimitive::kByte = CXXPrimitive("char", CXXPrimitive::CXXPrimitiveType::BYTE);
    const CXXPrimitive CXXPrimitive::kShort = CXXPrimitive("short", CXXPrimitive::CXXPrimitiveType::SHORT);
    const CXXPrimitive CXXPrimitive::kInt = CXXPrimitive("int", CXXPrimitive::CXXPrimitiveType::INT);
    const CXXPrimitive CXXPrimitive::kLong = CXXPrimitive("long", CXXPrimitive::CXXPrimitiveType::LONG);
    const CXXPrimitive CXXPrimitive::kUByte = CXXPrimitive("unsigned char",
                                                           (CXXPrimitive::CXXPrimitiveType) (
                                                                   CXXPrimitive::CXXPrimitiveType::UNSIGNED |
                                                                   CXXPrimitive::CXXPrimitiveType::BYTE
                                                           ));
    const CXXPrimitive CXXPrimitive::kUShort = CXXPrimitive("unsigned short",
                                                            (CXXPrimitive::CXXPrimitiveType) (
                                                                    CXXPrimitive::CXXPrimitiveType::UNSIGNED |
                                                                    CXXPrimitive::CXXPrimitiveType::SHORT
                                                            ));
    const CXXPrimitive CXXPrimitive::kUInt = CXXPrimitive("unsigned int",
                                                          (CXXPrimitive::CXXPrimitiveType) (
                                                                  CXXPrimitive::CXXPrimitiveType::UNSIGNED |
                                                                  CXXPrimitive::CXXPrimitiveType::INT
                                                          ));
    const CXXPrimitive CXXPrimitive::kULong = CXXPrimitive("unsigned long", (CXXPrimitive::CXXPrimitiveType) (
            CXXPrimitive::CXXPrimitiveType::UNSIGNED |
            CXXPrimitive::CXXPrimitiveType::LONG
    ));
    const CXXPrimitive CXXPrimitive::kFloat = CXXPrimitive("float", CXXPrimitive::CXXPrimitiveType::FLOAT);
    const CXXPrimitive CXXPrimitive::kDouble = CXXPrimitive("double", CXXPrimitive::CXXPrimitiveType::DOUBLE);

    CXXPointer::CXXPointer(
            const std::string &name,
            const CXXType &pointerType
    ) :

            CXXType(name),
            pointerType(pointerType) {}

    CXXAccessModifier getAccessModifier(const std::string &name) {
        if (name == "private") {
            return CXXAccessModifier::PRIVATE;
        }
        if (name == "public") {
            return CXXAccessModifier::PUBLIC;
        }
        if (name == "protected") {
            return CXXAccessModifier::PROTECTED;
        }
        if (name.empty()) {
            return CXXAccessModifier::INTERNAL;
        }
        return CXXAccessModifier::INVALID;
    }

    CXXParent::CXXParent(const std::string &parentName, CXXAccessModifier accessModifier) : parentName(parentName),
                                                                                            accessModifier(
                                                                                                    accessModifier) {}

    std::ostream &operator<<(std::ostream &os, const CXXParent &parent) {
        return os << "CXXParent(parentName: " << parent.parentName << ", accessModifier: " << parent.accessModifier << ")";
    }

    std::ostream &operator<<(std::ostream &stream, CXXAccessModifier modifier) {
        switch (modifier) {
            case INVALID:
                stream << "INVALID";
                break;
            case PRIVATE:
                stream << "private";
                break;
            case PROTECTED:
                stream << "protected";
                break;
            case PUBLIC:
                stream << "public";
                break;
            case INTERNAL:
                stream << "internal";
                break;
        }
        return stream;
    }

    CXXEnum::CXXEnumConstant::CXXEnumConstant(const std::string &name, size_t value) : CXXIdentifiable(name),
                                                                                       value(value) {}

    std::ostream &operator<<(std::ostream &os, const CXXEnum::CXXEnumConstant &constant) {
        os << "CXXEnum::CXXEnumConstants(name: " << constant.getName() << ", value: " << constant.value << ")";
        return os;
    }

    CXXEnum::CXXEnum(
            const std::string &name,
            const std::vector<CXXEnum::CXXEnumConstant> &contants
    ) : CXXType(name), contants(contants) {}

    CXXField::CXXField(
            const std::string &name,
            CXXAccessModifier accessModifier,
            const std::vector<CXXMacroExpansion> &macros,
            const std::string &type
    ) : CXXMember(name, accessModifier, macros), type(type) {}

    const std::string &CXXField::getType() const {
        return type;
    }

    CXXClass::CXXClass(const std::string &name, const std::vector<CXXField> &fields,
                       const std::vector<CXXParent> &parents) : CXXType(name), fields(fields), parents(parents) {}

    const std::vector<CXXField> &CXXClass::getFields() const {
        return fields;
    }

    const std::vector<CXXParent> &CXXClass::getParents() const {
        return parents;
    }
}
