#include "Lexer.h"
#include "MatcherAutomaton.h"
#include "StringAutomaton.h"
#include "IdentifierAutomaton.h"
#include "CommentAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
    lineNumber = 1;
}

Lexer::~Lexer() {
    for (Automaton* automaton: automata) {
        delete automaton;
    }
    for (Token* token : tokens) {
        delete token;
    }
    automata.clear();
    tokens.clear();
}

void Lexer::CreateAutomata() {

    // Ordered by precedence
    // Identifier could probably be before single chars but idk, it works
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());

    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));

    automata.push_back(new MatcherAutomaton(":", TokenType::COLON));
    automata.push_back(new MatcherAutomaton(":-", TokenType::COLON_DASH));
    automata.push_back(new MatcherAutomaton("+", TokenType::ADD));
    automata.push_back(new MatcherAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new MatcherAutomaton(".", TokenType::PERIOD));
    automata.push_back(new MatcherAutomaton(",", TokenType::COMMA));
    automata.push_back(new MatcherAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new MatcherAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", TokenType::RIGHT_PAREN));

    automata.push_back(new IdentifierAutomaton());

}

void Lexer::Run(std::string& input) {

    lineNumber = 1;
    int maxRead = 0;
    Automaton* maxAutomaton = nullptr;

    // While there are more characters to tokenize
    while(input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata.at(0);

        // Skip any whitespace
        if (isspace(input.at(0))) {
	    if (input.at(0) == '\n') lineNumber++;
            input.erase(0,1);
            continue;
        }

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        for (Automaton* automaton : automata){
            int inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }
        // Here is the "Max" part of the algorithm
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();

            if (newToken->GetType() != TokenType::COMMENT) {
                tokens.push_back(newToken);
            }
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0,1),lineNumber);
            tokens.push_back(newToken);
        }
        // Update `input` by removing characters read to create Token
        input.erase(0, maxRead);
    }
    // Add EOF token to end of collection
    tokens.push_back(new Token(TokenType::END_FILE,"", lineNumber));
}

std::vector<Token*> Lexer::GetTokens() {
    std::vector<Token*> new_tokens(tokens.size());
    std::copy(tokens.begin(), tokens.end(), new_tokens.begin());
    return new_tokens;
}

std::string Lexer::ToString() {
    std::ostringstream os;
    for (Token* token : tokens) {
        os << *token;
    }
    os << "Total Tokens = " << tokens.size();
    return os.str();
}

