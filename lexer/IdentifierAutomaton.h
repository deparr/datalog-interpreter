
#ifndef IDENTIFIERAUTOMATON_H
#define IDENTIFIERAUTOMATON_H

#include "Automaton.h"

class IdentifierAutomaton : public Automaton {
private:
    void AdvanceState();
    void S1(const std::string& input);
    void S2(const std::string& input);
public:
    IdentifierAutomaton() : Automaton(TokenType::ID) {}
    ~IdentifierAutomaton() = default;

    void S0(const std::string& input);
};

#endif //IDENTIFIERAUTOMATON_H
