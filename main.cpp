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

void runFile(const char* filename) {
    std::string line;
    plox::Lexer lexer;
    std::ifstream ifs{filename};
    while (std::getline(ifs, line)) {
        lexer.processLine(line);
    }

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
