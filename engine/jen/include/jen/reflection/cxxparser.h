#ifndef SHIROIENGINE_CXXPARSER_H
#define SHIROIENGINE_CXXPARSER_H

#include <jen/reflection/cxxclass.h>
#include <filesystem>
#include <clang-c/Index.h>
#include <types.h>
#include <glog/logging.h>
#include <jen/utility/clang_utility.h>

namespace shiroi::jen::reflection {
    class CXXUnit {
    private:

        std::vector<CXXClass> classes;
        std::vector<CXXMethod> methods;
    public:
        CXXUnit(const std::vector<CXXClass> &classes, const std::vector<CXXMethod> &methods);

        const std::vector<CXXClass> &getClasses() const;

        const std::vector<CXXMethod> &getMethods() const;
    };

    CXXUnit parse(
            std::filesystem::path file,
            std::vector<std::filesystem::path> includeDirectories
    );
}
#endif
