#pragma once

#include <string>
#include <vector>
#include <token.hpp>

namespace plox {

class Lexer {
    std::string source{};
    bool hasError = false;
    std::size_t start{};
    std::size_t current{};
    std::size_t line{};
    std::vector<Token> tokens{};

    void report(const std::size_t line, const std::string& where, const std::string &msg);
    void scanToken();
    void addToken(const TokenType type);

public:
    std::vector<Token> processFile(const std::string& source);
    void processLine(const std::string& line);
    void error(const std::size_t line, const std::string& msg);
    bool hadError() const;
};

}
