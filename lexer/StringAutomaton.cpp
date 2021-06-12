#include "StringAutomaton.h"

void StringAutomaton::Invalidate() {
    type = TokenType::UNDEFINED;
}

void StringAutomaton::AdvanceState() {
    inputRead++;
    index++;
}

void StringAutomaton::S0(const std::string& input) {
    // String must start with "'"
    if (input[index] == '\'') {
        AdvanceState();
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    // Another "'" is either the end of string or an escape char
    if (input[index] == '\'') {
        AdvanceState();
        S3(input);
    }

    // One open-ended "'" invalidates the string
    else if (input.size() == 1){
        AdvanceState();
        Invalidate();
    }

    // Any other chars are valid in string, including newlines
    else {
        if (input[index] == '\n') newLines++;
        AdvanceState();
        S2(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    // In the loop state, "'" can end string or escape a "'"
    if (input[index] == '\'') {
        AdvanceState();
        S3(input);
    }

    // EOF invalidates string
    else if (index == (int)(input.size() - 1)) {
        AdvanceState();
        Invalidate();
        newLines++;
    }
    else {
        if (input[index] == '\n') newLines++;
        AdvanceState();
        S2(input);
    }
}

// Accept/End state
void StringAutomaton::S3(const std::string& input) {

    // A "'" proceeding another "'" is escaped and returns flow to loop state
    if (input[index] == '\'') {
        AdvanceState();
        S2(input);
    }
    // Any other char proceeding a second "'" validates the string
}
