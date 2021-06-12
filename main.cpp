#include <iostream>
#include <fstream>
#include <string>

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "inter/Interpreter.h"
#include "inter/Database.h"

int main(int argc, char* argv[] ) {
    if (argc < 2) {
        std::cout << "need args\n"; return 0;
    }
    std::ifstream& in = *(new std::ifstream(argv[1]));
    if (!in) std::cout << "Unable to open input file: " << argv[1] << std::endl;

    // Convert file into single string
    std::ostringstream oss;
    oss << in.rdbuf();
    std::string fileAsString = oss.str();

    // Run lexer and get tokens
    Lexer* lexer = new Lexer();
    lexer->Run(fileAsString);
    std::vector<Token*> tokens = lexer->GetTokens();

    // Parse tokens against grammar
    Parser* parser = new Parser();
    DatalogProgram* program = new auto(parser->ParseProgram(tokens));
    std::vector<Predicate>* schemes = program->GetSchemes();
    std::vector<Predicate>* facts = program->GetFacts();
    std::vector<Rule>* rules = program->GetRules();
    std::vector<Predicate>* queries = program->GetQueries();

    // Use relational rules to evaluate a valid program
    Database* database = new Database();
    Interpreter* interpreter = new Interpreter(schemes, facts, rules, queries, database);

    interpreter->InterpretProgram();


    delete lexer;
    delete parser;
    delete program;
    delete database;
    delete interpreter;
    delete &in;

    return 0;

}
