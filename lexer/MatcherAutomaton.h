#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

#include "Automaton.h"

class MatcherAutomaton : public Automaton {
private:
    std::string toAccept;
public:
    MatcherAutomaton(std::string buildStr, TokenType type) : Automaton(type) { toAccept = buildStr; }
    ~MatcherAutomaton() = default;

    void S0(const std::string& input) override;
};

#endif // MATCHERAUTOMATON_H
