#include "CommentAutomaton.h"

void CommentAutomaton::AdvanceState() {
    inputRead++;
    index++;
}

void CommentAutomaton::Invalidate() {
    type = TokenType::UNDEFINED;
}

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        AdvanceState();
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string &input) {
    // A newline in a single line comment terminates the comment
    if (input[index] == '\n') {
        return;
    }

    // EOF also terminates a single line comment
    else if (index == (int)(input.size() - 1)) {
        newLines++;
        return;
    }

    // Check second char in slc to make multi-line comment
    else if (input[index] == '|') {
        AdvanceState();
        S3(input);

    }
    // Anything else advances to the slc loop state
    else {
        AdvanceState();
        S2(input);
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if (input[index] == '\n') {
        return;
    }

    // Check for EOF
    else if (index == (int)(input.size() - 1)) {
        newLines++;
        AdvanceState();
    }
    else {
        AdvanceState();
        S2(input);
    }
}

void CommentAutomaton::S3(const std::string& input) {
    // EOF in the multi-line loop state invalidates the comment
    if (index == (int)(input.size() - 1)) {
        AdvanceState();
        Invalidate();
        newLines++;
    }

    // A bar could mean the closing of a mlc
    else if (input[index] == '|') {
        AdvanceState();
        S4(input);
    }

    // Anything else is valid, including newlines
    else {
	    if (input[index] == '\n') newLines++;
            AdvanceState();
            S3(input);
    }
}

void CommentAutomaton::S4(const std::string& input) {
    if (index == (int)(input.size() - 1)) {
        AdvanceState();
        Invalidate();
        newLines++;
    }

    // The sequence "|#" validates the mlc
    else if (input[index] == '#') {
        AdvanceState();
    }
    // A single | leads back to the loop state
    else {
	if (input[index] == '\n') newLines++;
        AdvanceState();
        S3(input);
    }
}
