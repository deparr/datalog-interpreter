#ifndef PREDICATE_H
#define PREDICATE_H

#include <vector>
#include <sstream>
#include "Parameter.h"

class Predicate {
private:
    std::string mainID;
    std::vector<Parameter*> parameterList;
public:
    explicit Predicate(std::string name) : mainID(name), parameterList() {}
    ~Predicate() = default;

    void AddParameter(Parameter* newParam) { parameterList.push_back(newParam); }
    std::string GetParameter(size_t index) const { return **parameterList[index]; }
    Parameter GetWholeParameter(size_t index) const { return *parameterList[index]; }
    size_t ListSize() const { return parameterList.size(); }

    std::string ToString();
    friend std::ostream& operator<<(std::ostream& os, Predicate predicate) {
        os << predicate.ToString();
        return os;
    };

    std::string operator*() const { return mainID; }

};
#endif // PREDICATE_H