#include "Parser.h"

/*
 *  datalogProgram -> SCHEMES COLON schemeList FACTS COLON factList
 *      RULES COLON ruleList QUERIES COLON query queryList EOF
 *
 *  schemeList -> scheme schemeList | lambda
 *  factList
 *  ruleList
 *  queryList
 *
 *  scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
 *  fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
 *  rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
 *  query	    ->      predicate Q_MARK

    headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

    predicateList	->	COMMA predicate predicateList | lambda
    parameterList	-> 	COMMA parameter parameterList | lambda
    stringList	-> 	COMMA STRING stringList | lambda
    idList  	-> 	COMMA ID idList | lambda
    parameter	->	STRING | ID
 */


std::unordered_set<TokenType> Parser::FIRST(Nonterminal nonterm) {
    firstSet.clear();
    switch(nonterm) {
        case Nonterminal::DATALOG_PROGRAM:
            firstSet.insert(TokenType::SCHEMES);
            break;

        case Nonterminal::PREDICATE_LIST:
        case Nonterminal::STRING_LIST:
        case Nonterminal::PARAMETER_LIST:
        case Nonterminal::ID_LIST:
            firstSet.insert(TokenType::COMMA);
            break;

        case Nonterminal::PARAMETER:
            firstSet.insert(TokenType::STRING);
            firstSet.insert(TokenType::ID);
            break;

        default:
            firstSet.insert(TokenType::ID);
    }

    return firstSet;
}

DatalogProgram Parser::ParseProgram(std::vector<Token*>& tokens) {

    DatalogProgram newProgram;

    try {
        if (FIRST(Nonterminal::DATALOG_PROGRAM).count(tokens[0]->GetType())) {

            // Production: SCHEMES COLON schemeList
            tokens.erase(tokens.begin());
            if (tokens[0]->GetType() == TokenType::COLON) tokens.erase(tokens.begin());
            else throw std::string("COLON");
            newProgram.AddScheme(ParseScheme(tokens));
            ParseSchemeList(tokens, newProgram);

            // FACTS COLON factList
            tokens.erase(tokens.begin());
            if (tokens[0]->GetType() == TokenType::COLON) tokens.erase(tokens.begin());
            else throw std::string("COLON");
            ParseFactList(tokens, newProgram);

            // RULES COLON ruleList
            tokens.erase(tokens.begin());
            if (tokens[0]->GetType() == TokenType::COLON) tokens.erase(tokens.begin());
            else throw std::string("COLON");
            ParseRuleList(tokens, newProgram);

            // QUERIES COLON query queryList EOF
            tokens.erase(tokens.begin());
            if (tokens[0]->GetType() == TokenType::COLON) tokens.erase(tokens.begin());
            else throw std::string("COLON");
            newProgram.AddQuery(ParseQuery(tokens));
            ParseQueryList(tokens, newProgram);
            tokens.erase(tokens.begin());
        }
        else throw std::string("SCHEMES");
    }
    catch(std::string& err) {
        return newProgram;
    }

    newProgram.GoodProgram();
    newProgram.ConstructDomain();
    return newProgram;
}

Predicate Parser::ParseScheme(std::vector<Token*>& tokens) {
    // ID LEFT_PAREN ID idList RIGHT_PAREN
    if (FIRST(Nonterminal::SCHEME).count(tokens[0]->GetType())) {
        Predicate scheme(tokens[0]->GetDesc());
        tokens.erase(tokens.begin());

        if (tokens[0]->GetType() == TokenType::LEFT_PAREN) {
            tokens.erase(tokens.begin());

            if (tokens[0]->GetType() == TokenType::ID) {
                scheme.AddParameter(new Parameter(tokens[0]->GetDesc(), 0));
                tokens.erase(tokens.begin());
                ParseIDList(tokens, scheme);
            }
            else throw std::string("ID");

            // RIGHT_PAREN
            tokens.erase(tokens.begin());
            return scheme;

        }
        else throw std::string("LEFT_PAREN");
    }
    else throw std::string("ID");
}

void Parser::ParseSchemeList(std::vector<Token*>& tokens, DatalogProgram& program) {
    // Check if next token is follow set or first set
    // Production : lambda
    if (tokens[0]->GetType() == TokenType::FACTS) {
        return;
    }
    // Production : scheme schemeList
    else if (FIRST(Nonterminal::SCHEME_LIST).count(tokens[0]->GetType())) {
        program.AddScheme(ParseScheme(tokens));
        ParseSchemeList(tokens, program);
    }
    else throw std::string("ID");

}

void Parser::ParseIDList(std::vector<Token*>& tokens, Predicate& predicate) {
    // Check if next token is follow or first set
    // Production : lambda
    if (tokens[0]->GetType() == TokenType::RIGHT_PAREN) {
        return;
    }
    // Production : COMMA ID idList
    else if (FIRST(Nonterminal::ID_LIST).count(tokens[0]->GetType())) {
        // COMMA
        tokens.erase(tokens.begin());
        if (tokens[0]->GetType() == TokenType::ID) {
            predicate.AddParameter(new Parameter(tokens[0]->GetDesc(), 0));
            tokens.erase(tokens.begin());
            ParseIDList(tokens, predicate);
        }
        else throw std::string("ID");
    }
    else throw std::string("COMMA");
}

Predicate Parser::ParseFact(std::vector<Token*>& tokens) {
    // ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    Predicate fact(tokens[0]->GetDesc());
    tokens.erase(tokens.begin());

    if (tokens[0]->GetType() == TokenType::LEFT_PAREN) {
        tokens.erase(tokens.begin());

        if (tokens[0]->GetType() == TokenType::STRING) {
            fact.AddParameter(new Parameter(tokens[0]->GetDesc(), 1));
            tokens.erase(tokens.begin());
            ParseStringList(tokens, fact);

            // RIGHT_PAREN
            tokens.erase(tokens.begin());
            if (tokens[0]->GetType() == TokenType::PERIOD) {
                tokens.erase(tokens.begin());
                return fact;
            }
            else throw std::string("PERIOD");
        }
        else throw std::string("STRING");
    }
    else throw std::string("LEFT_PAREN");
}

void Parser::ParseFactList(std::vector<Token*>& tokens, DatalogProgram& program) {
    // Check whether follow or first set
    // Production : lambda
    if (tokens[0]->GetType() == TokenType::RULES) {
        return;
    }
    // Production : fact factList
    else if (FIRST(Nonterminal::FACT_LIST).count(tokens[0]->GetType())) {
        program.AddFact(ParseFact(tokens));
        ParseFactList(tokens, program);
    }
    else throw std::string("ID");

}

void Parser::ParseStringList(std::vector<Token*>& tokens, Predicate& predicate) {
    // Production : lambda
    if (tokens[0]->GetType() == TokenType::RIGHT_PAREN) {
        return;
    }
    // Production : COMMA STRING stringList
    else if (FIRST(Nonterminal::STRING_LIST).count(tokens[0]->GetType())) {
        // COMMA
        tokens.erase(tokens.begin());
        if (tokens[0]->GetType() == TokenType::STRING) {
            predicate.AddParameter(new Parameter(tokens[0]->GetDesc(), 1));
            tokens.erase(tokens.begin());
            ParseStringList(tokens, predicate);
        }
        else throw std::string("STRING");
    }
    else throw std::string("COMMA");
}

Rule Parser::ParseRule(std::vector<Token*>& tokens) {
    // headPredicate COLON_DASH predicate predicateList PERIOD
    if (FIRST(Nonterminal::HEAD_PREDICATE).count(tokens[0]->GetType())) {
        Rule newRule(ParseHeadPredicate(tokens));

        if (tokens[0]->GetType() == TokenType::COLON_DASH) {
            tokens.erase(tokens.begin());
            newRule.AddPredicate(ParsePredicate(tokens));
            ParsePredicateList(tokens, newRule);

            // PERIOD
            tokens.erase(tokens.begin());
            return newRule;
        }
        else throw std::string("COLON_DASH");
    }
    else throw std::string("ID");
}

void Parser::ParseRuleList(std::vector<Token*>& tokens, DatalogProgram& program) {
    // Check follow set
    // Production : lambda
    if (tokens[0]->GetType() == TokenType::QUERIES) {
        return;
    }
    // Production : rule ruleList
    else if (FIRST(Nonterminal::RULE_LIST).count(tokens[0]->GetType())) {
        program.AddRule(ParseRule(tokens));
        ParseRuleList(tokens, program);
    }
    else throw std::string("ID");
}

Predicate Parser::ParseHeadPredicate(std::vector<Token*>& tokens) {
    // ID LEFT_PAREN ID idList RIGHT_PAREN;
    Predicate newHeadPredicate(tokens[0]->GetDesc());
    tokens.erase(tokens.begin());

    if (tokens[0]->GetType() == TokenType::LEFT_PAREN) {
        tokens.erase(tokens.begin());

        if (tokens[0]->GetType() == TokenType::ID) {
            newHeadPredicate.AddParameter(new Parameter(tokens[0]->GetDesc(), 0));
            tokens.erase(tokens.begin());
            ParseIDList(tokens, newHeadPredicate);

            // RIGHT_PAREN
            tokens.erase(tokens.begin());
            return newHeadPredicate;
        }
        else throw std::string("ID");
    }
    else throw std::string("LEFT_PAREN");
}

Predicate Parser::ParsePredicate(std::vector<Token*>& tokens) {
    // ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    if (FIRST(Nonterminal::PREDICATE).count(tokens[0]->GetType())) {
        Predicate newPredicate(tokens[0]->GetDesc());
        tokens.erase(tokens.begin());

        if (tokens[0]->GetType() == TokenType::LEFT_PAREN) {
            tokens.erase(tokens.begin());

            newPredicate.AddParameter(ParseParameter(tokens));
            ParseParameterList(tokens, newPredicate);

            // RIGHT_PAREN
            tokens.erase(tokens.begin());
            return newPredicate;

        }
        else throw std::string("LEFT_PAREN");
    }
    else throw std::string("ID");
}

void Parser::ParsePredicateList(std::vector<Token*>& tokens, Rule& rule) {
    // Check for follow set first
    // Production : lambda
    if (tokens[0]->GetType() == TokenType::PERIOD) {
        return;
    }
    // Production : COMMA predicate predicateList
    else if (FIRST(Nonterminal::PREDICATE_LIST).count(tokens[0]->GetType())) {
        tokens.erase(tokens.begin());
        rule.AddPredicate(ParsePredicate(tokens));
        ParsePredicateList(tokens, rule);
    }
    else throw std::string("COMMA");
}

Parameter* Parser::ParseParameter(std::vector<Token*>& tokens) {
    // STRING | ID
    if (FIRST(Nonterminal::PARAMETER).count(tokens[0]->GetType())) {
        Parameter* newParam;
        if (tokens[0]->GetType() == TokenType::ID) {
            newParam = new Parameter(tokens[0]->GetDesc(), 0);
        }
        else {
            newParam = new Parameter(tokens[0]->GetDesc(), 1);
        }
        tokens.erase(tokens.begin());
        return newParam;
    }
    else throw std::string("STRING or ID");
}

void Parser::ParseParameterList(std::vector<Token*>& tokens, Predicate& predicate) {
    // Production : lambbda
    if (tokens[0]->GetType() == TokenType::RIGHT_PAREN) {
        return;
    }
    // Production : COMMA parameter parameterList
    else if (FIRST(Nonterminal::PARAMETER_LIST).count(tokens[0]->GetType())) {
        tokens.erase(tokens.begin());
        predicate.AddParameter(ParseParameter(tokens));
        ParseParameterList(tokens, predicate);
    }
    else throw std::string("COMMA");
}

Predicate Parser::ParseQuery(std::vector<Token*>& tokens) {
    // predicate Q_MARK
    if (FIRST(Nonterminal::QUERY).count(tokens[0]->GetType())) {
        Predicate query = ParsePredicate(tokens);

        if (tokens[0]->GetType() == TokenType::Q_MARK) {
            tokens.erase(tokens.begin());
            return query;
        }
        else throw std::string("Q_MARK");
    }
    else throw std::string("ID");
}

void Parser::ParseQueryList(std::vector<Token*>& tokens, DatalogProgram& program) {
    // Production : lambda
    // Woo hoo! We made it!
    if (tokens[0]->GetType() == TokenType::END_FILE) {
        return;
    }
    // Production : query queryList
    else if (FIRST(Nonterminal::QUERY_LIST).count(tokens[0]->GetType())) {
        program.AddQuery(ParseQuery(tokens));
        ParseQueryList(tokens, program);
    }
    else throw std::string("ID");
}
