#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
   this->type = type;
   desc = description;
   this->line = line;
}

std::string Token::GetTypeString() {
    std::string typeString;
    switch(this->type) {
        case TokenType::END_FILE:
            typeString = "EOF";
            break;
        case TokenType::ID:
            typeString = "ID";
            break;
        case TokenType::STRING:
            typeString = "STRING";
            break;
        case TokenType::COMMENT:
            typeString = "COMMENT";
            break;
        case TokenType::COMMA:
            typeString = "COMMA";
            break;
        case TokenType::PERIOD:
            typeString = "PERIOD";
            break;
        case TokenType::Q_MARK:
            typeString = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN:
            typeString = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            typeString = "RIGHT_PAREN";
            break;
        case TokenType::COLON:
            typeString = "COLON";
            break;
        case TokenType::COLON_DASH:
            typeString = "COLON_DASH";
            break;
        case TokenType::MULTIPLY:
            typeString = "MULTIPLY";
            break;
        case TokenType::ADD:
            typeString = "ADD";
            break;
        case TokenType::SCHEMES:
            typeString = "SCHEMES";
            break;
        case TokenType::FACTS:
            typeString = "FACTS";
            break;
        case TokenType::RULES:
            typeString = "RULES";
            break;
        case TokenType::QUERIES:
            typeString = "QUERIES";
            break;
        default:
            typeString = "UNDEFINED";
    }
    return typeString;
}

// Get type string of any type
/*std::string Token::GetTypeString(TokenType type) {
    std::string typeString;
    switch(type) {
        case TokenType::END_FILE:
            typeString = "EOF";
            break;
        case TokenType::ID:
            typeString = "ID";
            break;
        case TokenType::STRING:
            typeString = "STRING";
            break;
        case TokenType::COMMENT:
            typeString = "COMMENT";
            break;
        case TokenType::COMMA:
            typeString = "COMMA";
            break;
        case TokenType::PERIOD:
            typeString = "PERIOD";
            break;
        case TokenType::Q_MARK:
            typeString = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN:
            typeString = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            typeString = "RIGHT_PAREN";
            break;
        case TokenType::COLON:
            typeString = "COLON";
            break;
        case TokenType::COLON_DASH:
            typeString = "COLON_DASH";
            break;
        case TokenType::MULTIPLY:
            typeString = "MULTIPLY";
            break;
        case TokenType::ADD:
            typeString = "ADD";
            break;
        case TokenType::SCHEMES:
            typeString = "SCHEMES";
            break;
        case TokenType::FACTS:
            typeString = "FACTS";
            break;
        case TokenType::RULES:
            typeString = "RULES";
            break;
        case TokenType::QUERIES:
            typeString = "QUERIES";
            break;
        default:
            typeString = "UNDEFINED";
    }
    return typeString;
} */

TokenType& Token::GetType() {
    return this->type;
}

std::string Token::ToString(void) {
    std::ostringstream os;
    os << "(" << GetTypeString() << ",\"" << desc << "\"," << line << ")\n";
    return os.str();
}
