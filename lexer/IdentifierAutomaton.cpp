#include "IdentifierAutomaton.h"

void IdentifierAutomaton::AdvanceState() {
    inputRead++;
    index++;
}

void IdentifierAutomaton::S0(const std::string &input) {
    if (isalpha(input[index])) {
        AdvanceState();
        S1(input);
    }
    else {
        Serr();
    }
}

void IdentifierAutomaton::S1(const std::string &input) {
    if (isalnum(input[index])) {
        AdvanceState();
        S2(input);
    }
    else {
        return;
    }
}

void IdentifierAutomaton::S2(const std::string &input) {
    if (isalnum(input[index])) {
        AdvanceState();
        S2(input);
    }
}
