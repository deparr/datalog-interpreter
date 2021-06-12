#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <sstream>

enum class TokenType {
    UNDEFINED, END_FILE,
    ID, STRING,
    COMMENT, COMMA,
    PERIOD, Q_MARK,
    LEFT_PAREN, RIGHT_PAREN,
    COLON, COLON_DASH,
    MULTIPLY, ADD,
    SCHEMES, FACTS,
    RULES, QUERIES
};

class Token
{
private:
    TokenType type;
    std::string desc;
    int line;

    // Theres gotta be a better way to do this....


public:
    Token(TokenType type, std::string description, int line);

    TokenType& GetType();
    std::string GetTypeString();
//    std::string GetTypeString(TokenType);
    std::string GetDesc() {
        return desc;
    }

    std::string ToString();
    friend std::ostream& operator<<(std::ostream& os, Token& token) {
        os << token.ToString();
        return os;
    }


};

#endif // TOKEN_H
