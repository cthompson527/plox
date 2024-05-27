#include <cassert>
#include <iostream>
#include <lexer.hpp>
#include <token.hpp>

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
  auto isNext = [&](const char ch) {
    if (current == source.length())
      return false;
    if (ch != source[current]) {
      return false;
    }
    current++;
    return true;
  };
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
  case '!': addToken(isNext('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
  case '=': addToken(isNext('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
  case '<': addToken(isNext('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
  case '>': addToken(isNext('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
  case '/': 
            if (isNext('/')) {
              while(current < source.length() and source[++current] != '\n') {}
              line++;
            } else {
              addToken(TokenType::SLASH); 
            }
            break;
  case ' ':
  case '\r':
  case '\t': break;
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
// hello!

} // namespace plox
