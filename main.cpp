#include <iostream>
#include <cassert>
#include <sysexits.h>
#include <lexer.hpp>

void runPrompt() {
    std::string line;
    std::cout << "> ";
    plox::Lexer lexer;
    while (std::getline(std::cin, line)) {
        lexer.processLine(line);
    }
}

void runFile(const char* filename) {
    assert(false && "Not implemented");
}

int main(int argc, const char* argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [script]\n";
        return EX_USAGE;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
    return 0;
}
