#include <iostream>
#include <sysexits.h>
#include <lexer.hpp>
#include <fstream>

void runPrompt() {
    std::string line;
    plox::Lexer lexer;
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        lexer.processLine(line);
        std::cout << "> ";
    }
}

int runFile(const char* filename) {
    std::string line;
    plox::Lexer lexer;
    std::ifstream ifs{filename};
    std::getline(ifs, line, '\0');
    lexer.processFile(line);
    if (lexer.hadError()) {
        return EX_DATAERR;
    }
    return EX_OK;
}

int main(int argc, const char* argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [script]\n";
        return EX_USAGE;
    } else if (argc == 2) {
        return runFile(argv[1]);
    } else {
        runPrompt();
    }
    return EX_OK;
}
