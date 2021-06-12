
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include <unordered_set>

#include "../lexer/Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"




enum class Nonterminal {
    DATALOG_PROGRAM,
    SCHEME_LIST, FACT_LIST, RULE_LIST,
    QUERY_LIST, SCHEME, FACT,
    RULE, QUERY, HEAD_PREDICATE,
    PREDICATE, PREDICATE_LIST,
    PARAMETER, PARAMETER_LIST,
    STRING_LIST, ID_LIST
};

class Parser {
private:
    std::unordered_set<TokenType> firstSet;

    std::unordered_set<TokenType> FIRST(Nonterminal);

    // LISTS
    void ParseSchemeList(std::vector<Token*>&, DatalogProgram&);
    void ParseIDList(std::vector<Token*>&, Predicate&);
    void ParseFactList(std::vector<Token*>&, DatalogProgram&);
    void ParseStringList(std::vector<Token*>&, Predicate&);
    void ParseRuleList(std::vector<Token*>&, DatalogProgram&);
    void ParsePredicateList(std::vector<Token*>&, Rule&);
    void ParseParameterList(std::vector<Token*>&, Predicate&);
    void ParseQueryList(std::vector<Token*>&, DatalogProgram&);

    // PREDICATES
    Predicate ParseScheme(std::vector<Token*>&);
    Predicate ParseFact(std::vector<Token*>&);
    Rule ParseRule(std::vector<Token*>&);
    Predicate ParseHeadPredicate(std::vector<Token*>&);
    Predicate ParsePredicate(std::vector<Token*>&);
    Parameter* ParseParameter(std::vector<Token*>&);
    Predicate ParseQuery(std::vector<Token*>&);



public:
    Parser() : firstSet() {}
    ~Parser() = default;

    DatalogProgram ParseProgram(std::vector<Token*>&);

};
#endif // PARSER_H
