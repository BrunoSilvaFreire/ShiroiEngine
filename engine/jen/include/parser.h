#ifndef SHIROIENGINE_PARSER_H
#define SHIROIENGINE_PARSER_H

#include <types.h>
#include <string>
#include <vector>
#include <filesystem>
#include <ostream>
#include <utility/string_utility.h>

class Token {
private:
    std::string value;
public:
    Token(const std::string &value) : value(value) {}

    const std::string &getValue() const {
        return value;
    }

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        return os << "Token(value: " << token.value << ")";
    }
};

class Tokenized {
private:
    std::vector<Token> tokens;
public:
    Tokenized(const std::vector<Token> &tokens) : tokens(tokens) {}

    const std::vector<Token> &getTokens() const {
        return tokens;
    }
};

inline Tokenized lex(std::string &source);

void generateTo(std::string &source, std::filesystem::path outputPath);

#endif //SHIROIENGINE_PARSER_H
