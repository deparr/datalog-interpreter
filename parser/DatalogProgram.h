#ifndef DATALOG_PROGRAM_H
#define DATALOG_PROGRAM_H
#include <vector>
#include <set>

#include "Rule.h"
#include "Predicate.h"

class DatalogProgram {
private:
    bool badProgram;
    std::vector<Predicate> schemeList;
    std::vector<Predicate> factList;
    std::vector<Rule> ruleList;
    std::vector<Predicate> queryList;
    std::set<std::string> domain;
public:
    DatalogProgram() : badProgram(true),
                        schemeList(),
                        factList(),
                        ruleList(),
                        queryList() {}
    ~DatalogProgram() = default;

    void AddRule(Rule);
    void AddScheme(Predicate);
    void AddFact(Predicate);
    void AddQuery(Predicate);

    std::vector<Predicate>* GetSchemes();
    std::vector<Predicate>* GetFacts();
    std::vector<Rule>* GetRules();
    std::vector<Predicate>* GetQueries();

    void ConstructDomain();

    void GoodProgram() { badProgram = false; }

    bool operator!() const {
     return !badProgram;
    }

    std::string ToString();
    friend std::ostream& operator<<(std::ostream& os, DatalogProgram& program) {
        os << program.ToString();
        return os;
    }
};


#endif // DATALOG_PROGRAM_H
