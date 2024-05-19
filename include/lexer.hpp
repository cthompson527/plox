#include <string>

namespace plox {

class Lexer {
    bool hasError{};

public:
    void processLine(const std::string& line);
};

}
