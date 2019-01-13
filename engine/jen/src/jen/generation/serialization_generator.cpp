#include <jen/generation/cxxgenerator.h>
#include <jen/generation/generated_source.h>

namespace shiroi::jen::generation {
#define SERIALIZATION_MACRO "SERIALIZE"

    class SerializationGenerator : public CXXGenerator {
        void generate(const reflection::CXXUnit &unit, const reflection::CXXClass &clazz,
                      CXXGenerationContext &context) override {

            GeneratedScope serializer = GeneratedScope::method(
                    "void",
                    "serialize",
                    std::vector<std::string>{"SerializedObject* obj"}
            );
            std::vector<reflection::CXXField> fields = std::vector<reflection::CXXField>(clazz.getFields());
            fields.erase(std::remove_if(fields.begin(), fields.end(), [](const reflection::CXXField &field) {
                return field.findMacroExpansion(SERIALIZATION_MACRO).isInvalid();
            }), fields.end());
            if (fields.empty()) {
                return;
            }
            for (const reflection::CXXField &field : fields) {
                const reflection::CXXMacroExpansion &ex = field.findMacroExpansion(SERIALIZATION_MACRO);
                if (ex.isInvalid()) {
                    continue;
                }
                const auto &typeName = field.getType();
                const auto &fieldName = field.getName();
                auto serializationLine = std::string("obj->write<").append(typeName).append(">(\"").append(
                        fieldName).append(
                        "\", ").append(fieldName).append(");");
                serializer.addLine(serializationLine);
            }
            std::vector<std::string> initializers;
            for (const reflection::CXXField &field : fields) {
                if (field.findMacroExpansion(SERIALIZATION_MACRO).isInvalid()) {
                    continue;
                }
                const auto &fName = field.getName();
                initializers.push_back(
                        std::string(fName).append("(obj->extract<").append(field.getType()).append(">(\"").append(
                                fName).append("\"))"));
            }
            GeneratedScope deserializer = GeneratedScope::constructor(
                    clazz.getName(),
                    std::vector<std::string>{
                            "Scene * scene",
                            "SerializedObject * obj"
                    }, initializers
            );

            context.addScope(serializer);
            context.addScope(deserializer);

        }
    };
}