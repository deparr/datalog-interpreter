#include "MatcherAutomaton.h"

void MatcherAutomaton::S0(const std::string &input) {
    bool accepted = true;
    for (size_t i = 0; i < toAccept.size() && accepted; i++) {
        index++; // Inc index to check for newLines on accepted automaton

        // Compare each char until the instantiated pattern is broken
        if (input[i] != toAccept[i]) {
            accepted = false;
        }
    }
    if (accepted) {
        inputRead = toAccept.size();
    }
}
