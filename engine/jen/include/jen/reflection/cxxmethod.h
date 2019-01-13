//
// Created by Bruno Silva Freire on 13/01/2019.
//

#ifndef SHIROIENGINE_CXXMETHOD_H
#define SHIROIENGINE_CXXMETHOD_H
namespace shiroi::jen::reflection {

    class CXXParameter : public CXXIdentifiable {
    private:
        CXXType *type;
    public:
        CXXParameter(const std::string &name, CXXType *type);

        CXXType *getType() const;
    };


    class CXXMethod : CXXIdentifiable {
    private:
        std::vector <CXXParameter> parameters;
    public:
        const std::vector <CXXParameter> &getParameters() const;
    };
}
#endif //SHIROIENGINE_CXXMETHOD_H
