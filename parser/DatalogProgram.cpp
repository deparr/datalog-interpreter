#include "DatalogProgram.h"


void DatalogProgram::AddRule(Rule rule) {
    ruleList.push_back(rule);
}

void DatalogProgram::AddScheme(Predicate scheme) {
    schemeList.push_back(scheme);
}

void DatalogProgram::AddFact(Predicate fact) {
    factList.push_back(fact);
}

void DatalogProgram::AddQuery(Predicate query) {
    queryList.push_back(query);
}

void DatalogProgram::ConstructDomain() {
    for (Predicate fact : factList) {
        for (size_t i = 0; i < fact.ListSize(); i++) {
            domain.insert(fact.GetParameter(i));
        }
    }
}

std::vector<Predicate>* DatalogProgram::GetSchemes() {
    return& schemeList;
}

std::vector<Predicate>* DatalogProgram::GetFacts() {
    return& factList;
}

std::vector<Rule>* DatalogProgram::GetRules() {
    return& ruleList;
}

std::vector<Predicate>* DatalogProgram::GetQueries() {
    return& queryList;
}

std::string DatalogProgram::ToString() {
    std::ostringstream os;
    os << "Schemes(" << schemeList.size() << "):\n";
    for (const Predicate& scheme : schemeList) {
        os << "  " << scheme << std::endl;
    }

    os << "Facts(" << factList.size() << "):\n";
    for (const Predicate& fact : factList) {
        os << "  " << fact << ".\n";
    }

    os << "Rules(" << ruleList.size() << "):\n";
    for (Rule rule : ruleList) {
        os << rule;
    }

    os << "Queries(" << queryList.size() << "):\n";
    for (const Predicate& query : queryList) {
        os << "  " << query << "?\n";
    }

    os << "Domain(" << domain.size() << "):\n";
    for (const std::string& param : domain) {
        os << "  " << param << std::endl;
    }
    return os.str();
}
