#include <cassert>
#include <iostream>
#include <lexer.hpp>

namespace plox {

std::vector<Token> Lexer::processFile(const std::string &src) {
  this->source = src;

  while (current < source.length()) {
    start = current;
    scanToken();
  }
  tokens.emplace_back(TokenType::END_OF_FILE, "", line);
  return tokens;
}

void Lexer::processLine(const std::string &) {
  // while (current < line.length()) {
  //     start = current;
  //     scanToken();
  // }
  // tokens.emplace_back(TokenType::EOF, "", line);
  assert(false && "not implemented");
}

void Lexer::scanToken() {
  char c = source[current++];
  switch (c) {
    // clang-format off
  case '(': addToken(TokenType::LEFT_PAREN); break;
  case ')': addToken(TokenType::RIGHT_PAREN); break;
  case '{': addToken(TokenType::LEFT_BRACE); break;
  case '}': addToken(TokenType::RIGHT_BRACE); break;
  case ',': addToken(TokenType::COMMA); break;
  case '.': addToken(TokenType::DOT); break;
  case '-': addToken(TokenType::MINUS); break;
  case '+': addToken(TokenType::PLUS); break;
  case ';': addToken(TokenType::SEMICOLON); break;
  case '*': addToken(TokenType::STAR); break;
  case '\n': line++; break;
  default: error(line, "unexpected cahracter");
    // clang-format on
  }
}

void Lexer::addToken(const TokenType type) {
  std::string str = source.substr(start, current);
  tokens.emplace_back(type, str, line);
}

void Lexer::error(const std::size_t line_no, const std::string &msg) {
  report(line_no, "", msg);
}

void Lexer::report(const std::size_t line_no, const std::string &where,
                   const std::string &msg) {
  std::cerr << "[line " << line_no << "] Error" << where << ": " << msg << "\n";
  hasError = true;
}

bool Lexer::hadError() const { return hasError; }

} // namespace plox
