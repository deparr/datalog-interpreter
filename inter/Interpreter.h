#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include "Database.h"
#include "../parser/Predicate.h"
#include "../parser/Rule.h"


class Interpreter {
private:
    std::vector<Predicate>* schemes;
    std::vector<Predicate>* facts;
    std::vector<Rule>* rules;
    std::vector<Predicate>* queries;
    Database* database;

    // Helpers`
    Relation* EvaluatePredicate(const Predicate& pred);

public:
    Interpreter(std::vector<Predicate>* newSchemes, std::vector<Predicate>* newFacts,
                std::vector<Rule>* newRules, std::vector<Predicate>* newQueries, Database* newDB)
                : schemes(newSchemes), facts(newFacts), rules(newRules),
                queries(newQueries), database(newDB) {};
    ~Interpreter() = default;

    void InterpretProgram();

};
#endif // INTERPRETER_H
