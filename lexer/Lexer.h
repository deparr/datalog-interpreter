#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    int lineNumber;

    void CreateAutomata();


public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);

    std::vector<Token*> GetTokens();

    std::string ToString();
    friend std::ostream& operator<<(std::ostream& os, Lexer& lexer) {
        os << lexer.ToString();
        return os;
    }

};

#endif // LEXER_H
