#include <jen/generation/generated_source.h>
#include <utility/string_utility.h>

namespace shiroi::jen::generation {
#define INDENT_SPACES 4

    std::string getIndentation(uint32 indentLevel) {
        std::string string;
        for (int i = 0; i < indentLevel; ++i) {
            for (int j = 0; j < INDENT_SPACES; ++j) {
                string += ' ';
            }
        }
        return string;
    }

    std::string GeneratedScope::parse(uint32 indentLevel) const {
        std::string str = header;
        bool braces = (flags & OptionFlags::BRACES) == OptionFlags::BRACES;
        if (braces) {
            str += getIndentation(indentLevel) + " {\n";
            indentLevel++;
        }

        for (auto &line : lines) {
            str += (getIndentation(indentLevel) + line + "\n");
        }
        indentLevel++;
        for (const GeneratedScope &child : children) {
            str += child.parse(indentLevel);
        }
        indentLevel--;
        if (braces) {
            str += getIndentation(indentLevel) + "}\n";
        }
        return str;
    }


    GeneratedScope::GeneratedScope(std::string title,
                                   GeneratedScope::OptionFlags flags,
                                   std::vector<std::string> lines,
                                   std::vector<GeneratedScope> children)
            : header(std::move(title)), flags(flags), lines(std::move(lines)), children(std::move(children)) {}

    GeneratedScope
    GeneratedScope::method(
            const std::string &returnType,
            const std::string &name,
            const std::vector<std::string> &params
    ) {
        auto finalName = returnType + " " + name + "(";
        for (int i = 0; i < params.size(); ++i) {
            finalName += params[i];
            if (i != params.size() - 1) {
                finalName += ", ";
            }
        }
        finalName += ") ";
        return GeneratedScope(finalName);
    }

    void GeneratedScope::addLine(const std::string &str) {
        lines.push_back(str);
    }

    GeneratedScope GeneratedScope::constructor(const std::string &clazz, std::vector<std::string> parameters,
                                               std::vector<std::string> initializers) {
        std::string cpy = clazz;
        cpy.append("(").append(shiroi::string_utility::join(parameters)).append(") ");
        if (!initializers.empty()) {
            cpy.append(": ")
                    .append(shiroi::string_utility::join(initializers));
        }
        return GeneratedScope(cpy);
    }
}