#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
    void Invalidate();
    void AdvanceState();

    void S1(const std::string& input);  // Possible end/accept state
    void S2(const std::string& input);  // Possible end/accept state
    void S3(const std::string& input);  // Possible end/accept state

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}
    ~StringAutomaton() = default;

    void S0(const std::string& input);

};

#endif // STRINGAUTOMATON_H
