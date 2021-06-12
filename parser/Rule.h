#ifndef RULE_H
#define RULE_H
#include "Predicate.h"


class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> predicateList;
public:
    Rule(Predicate headPred) : headPredicate(headPred) {}
    ~Rule() = default;

    void AddPredicate(Predicate newPredicate) {
        predicateList.push_back(newPredicate);
    }

    size_t Size() { return predicateList.size(); }
    size_t IsMultiRule() { return (predicateList.size() - 1); }
    Predicate& GetHeadPred() { return headPredicate; }
    Predicate operator[](size_t index) { return predicateList[index]; }

    std::string toString() {
        std::ostringstream os;

        // ID (ID, ..., ID) :-
        os << headPredicate << " :- ";

        // ID(parameter, ..., parameter) ... .
        os << predicateList[0];
        for (size_t i = 1; i < predicateList.size(); i++) {
            os << "," << predicateList[i];
        }
        os << ".\n";

        return os.str();
    }

    friend std::ostream& operator<<(std::ostream& os, Rule& rule) {
        os << rule.toString();
        return os;
    }

};
#endif // RULE_H