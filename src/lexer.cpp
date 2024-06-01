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

bool Lexer::isAtEnd() const { return current == source.length(); }

char Lexer::peek() const { return isAtEnd() ? '\0' : source[current]; }

bool Lexer::isDigit(const char ch) const { return ch >= '0' and ch <= '9'; }

bool Lexer::isAlpha(const char ch) const {
  return (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == '_';
}

bool Lexer::isAlphaNumeric(const char ch) const {
  return isAlpha(ch) or isDigit(ch);
}

void Lexer::scanToken() {
  char c = source[current++];
  auto isNext = [&](const char ch) {
    if (isAtEnd())
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
              while(not isAtEnd() and source[current++] != '\n') {}
            } else {
              addToken(TokenType::SLASH); 
            }
            break;
  case '"': string(); break;
  case ' ':
  case '\r':
  case '\t': break;
  case '\n': line++; break;
  default: if (isDigit(c)) {
             number();
           } else if (isAlpha(c)) {
             identifier();
           } else {
             error(line, "unexpected cahracter");
           }
    // clang-format on
  }
}

void Lexer::identifier() {
  while (isAlphaNumeric(peek())) {
    current++;
  }

  addToken(TokenType::IDENTIFIER);
}

void Lexer::number() {
  while (isDigit(peek())) {
    current++;
  }

  if (peek() == '.' and isDigit(source[current + 1])) {
    current++;

    while (isDigit(peek())) {
      current++;
    }
  }

  const auto &value = source.substr(start, current - start);
  addToken(TokenType::NUMBER, std::stod(value));
}

void Lexer::string() {
  while (peek() != '"' and not isAtEnd()) {
    if (peek() == '\n') {
      line++;
    }
    current++;
  }

  if (isAtEnd()) {
    error(line, "Unterminated string.");
    return;
  }

  const auto &value = source.substr(start + 1, current - start - 1);
  current++;
  addToken(TokenType::STRING, value);
}

void Lexer::addToken(const TokenType type) {
  std::string str = source.substr(start, current - start);
  tokens.emplace_back(type, str, line);
}

void Lexer::addToken(const TokenType type, std::any literal) {
  std::string str = source.substr(start, current - start);
  tokens.emplace_back(type, str, literal, line);
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
