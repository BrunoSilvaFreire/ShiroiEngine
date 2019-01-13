#ifndef SHIROIENGINE_GENERATOR_H
#define SHIROIENGINE_GENERATOR_H

#include <jen/queued_class.h>

namespace shiroi::jen {
    class GenerationProcessor;

    class CXXClass;

    class IGenerator {
    public:
        virtual std::string generate(GenerationProcessor *processor, CXXClass *clazz) = 0;
    };
}
#endif
