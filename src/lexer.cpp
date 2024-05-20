#include <lexer.hpp>
#include <iostream>

namespace plox {

void Lexer::processLine(const std::string& line) {
    for (const auto ch : line) {
        std::cout << ch << "\n";
    }
}

}
