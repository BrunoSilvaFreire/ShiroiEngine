
#ifndef SHIROIENGINE_CXXPRIMITIVES_H
#define SHIROIENGINE_CXXPRIMITIVES_H

#include <jen/reflection/cxxcore.h>

namespace shiroi::jen::reflection {

    class CXXPointer : CXXType {
    private:
        CXXType pointerType;
    public:
        CXXPointer(const std::string &name, const CXXType &pointerType);
    };

    class CXXEnum : public CXXType {
    public:
        class CXXEnumConstant : public CXXIdentifiable {
        private:
            size_t value;
        public:
            CXXEnumConstant(const std::string &name, size_t value);

            friend std::ostream &operator<<(std::ostream &os, const CXXEnumConstant &constant);
        };

    private:
        std::vector <CXXEnumConstant> contants;
    public:
        CXXEnum(const std::string &name, const std::vector <CXXEnumConstant> &contants);
    };

    class CXXPrimitive : CXXType {
    public:
        enum CXXPrimitiveType : uint8_t {
            BYTE = 1,
            SHORT = 2,
            INT = 3,
            LONG = 4,
            FLOAT = 5,
            DOUBLE = 6,
            UNSIGNED = 1 << 7
        };
    private:
        CXXPrimitive(const std::string &name, CXXPrimitiveType type) : CXXType(name), type(type) {}

        CXXPrimitiveType type;
    public:
        const static CXXPrimitive kByte, kShort, kInt, kLong;
        const static CXXPrimitive kUByte, kUShort, kUInt, kULong;
        const static CXXPrimitive kFloat, kDouble;

        bool isUnsigned() const;

        CXXPrimitiveType getType() const;
    };
}

#endif //SHIROIENGINE_CXXPRIMITIVES_H
