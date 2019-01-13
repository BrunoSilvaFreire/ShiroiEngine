

#ifndef SHIROIENGINE_CXXCORE_H
#define SHIROIENGINE_CXXCORE_H

#include <string>
namespace shiroi::jen::reflection {

    enum CXXAccessModifier {
        INVALID,
        PRIVATE,
        INTERNAL,
        PROTECTED,
        PUBLIC
    };

    CXXAccessModifier getAccessModifier(const std::string &name);

    class CXXIdentifiable {
    private:
        std::string name;
    public:
        explicit CXXIdentifiable(const std::string& name);

        const std::string getName() const;
    };

    class CXXType : public CXXIdentifiable {
    public:
        explicit CXXType(const std::string &name);
    };
}
#endif
