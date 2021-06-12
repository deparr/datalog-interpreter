#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton {
private:
    void AdvanceState();
    void Invalidate();

    void S1(const std::string& input);
    void S2(const std::string& input);  // Possible end/accept state
    void S3(const std::string& input);  // Possible end/accept state
    void S4(const std::string& input);  // Possible end/accept state
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}
    ~CommentAutomaton() = default;

    void S0(const std::string& input);
};

#endif // COMMENTAUTOMATON_H
