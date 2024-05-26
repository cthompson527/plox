#pragma once

#include <string>

namespace plox {

enum class TokenType {
  // single char
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // one or two chars
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // literals
  IDENTIFIER,
  STRING,
  NUMBER,

  // keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  END_OF_FILE
};

struct Token {
  TokenType type{};
  std::string lexeme{};
  std::uint16_t line{};

  Token(TokenType t, const std::string &l, const std::uint16_t li)
      : type(t), lexeme(l), line(li) {}

  std::string toString() {
    return std::to_string(static_cast<std::uint8_t>(type)) + " " + lexeme;
  }
};

} // namespace plox
