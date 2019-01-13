#ifndef SHIROIENGINE_SERIALIZATION_GENERATOR_H
#define SHIROIENGINE_SERIALIZATION_GENERATOR_H

#include <jen/generator.h>

namespace shiroi::jen {
    class SerializationGenerator : public shiroi::jen::IGenerator {
        std::string generate(GenerationProcessor *processor, CXXClass *clazz) override;
    };
}
#endif
