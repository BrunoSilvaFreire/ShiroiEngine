#include <jen/utility/generated_scope.h>

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

std::string shiroi::jen::utility::GeneratedScope::parse(uint32 indentLevel) {
    std::string str = title;
    bool braces = (flags & OptionFlags::BRACES) == OptionFlags::BRACES;
    if (braces) {
        str += getIndentation(indentLevel) + " {\n";
        indentLevel++;
    }

    for (auto &line : lines) {
        str += (getIndentation(indentLevel) + line + "\n");
    }
    indentLevel++;
    for (GeneratedScope &child : children) {
        str += child.parse(indentLevel);
    }
    indentLevel--;
    if (braces) {
        str += getIndentation(indentLevel) + "}\n";
    }
    return str;
}


shiroi::jen::utility::GeneratedScope::GeneratedScope(std::string title,
                                                     shiroi::jen::utility::GeneratedScope::OptionFlags flags,
                                                     std::vector<std::string> lines,
                                                     std::vector<shiroi::jen::utility::GeneratedScope> children)
        : title(std::move(title)), flags(flags), lines(std::move(lines)), children(std::move(children)) {}

shiroi::jen::utility::GeneratedScope
shiroi::jen::utility::GeneratedScope::method(
        const std::string &returnType,
        const std::string &name,
        const std::vector<std::string> &params
) {
    auto finalName = returnType + " " + name + " (";
    for (int i = 0; i < params.size(); ++i) {
        finalName += params[i];
        if (i != params.size() - 1) {
            finalName += ", ";
        }
    }
    finalName += ") ";
    return shiroi::jen::utility::GeneratedScope(finalName);
}

void shiroi::jen::utility::GeneratedScope::addLine(const std::string &str) {
    lines.push_back(str);
}
