#pragma once

#include <any>
#include <string>
#include <token.hpp>
#include <vector>

namespace plox {

class Lexer {
  std::string source{};
  bool hasError = false;
  std::size_t start{};
  std::size_t current{};
  std::size_t line{1};
  std::vector<Token> tokens{};

  void report(const std::size_t line, const std::string &where,
              const std::string &msg);
  void scanToken();
  void addToken(const TokenType type);
  void addToken(const TokenType type, std::any literal);
  bool isAlpha(const char ch) const;
  bool isAlphaNumeric(const char ch) const;
  void string();
  void number();
  void identifier();
  bool isDigit(const char ch) const;
  bool isAtEnd() const;
  char peek() const;

public:
  std::vector<Token> processFile(const std::string &source);
  void processLine(const std::string &line);
  void error(const std::size_t line, const std::string &msg);
  bool hadError() const;
};

} // namespace plox
