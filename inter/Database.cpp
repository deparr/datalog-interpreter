#include "Database.h"

void Database::AddRelation(Relation& newRelation) {
    relations[newRelation.GetName()] = newRelation;
}

void Database::MatchAddTuple(std::string relName, Tuple &tuple) {
    if (relations.count(relName)) {
        relations[relName].AddTuple(tuple);
    }
}

Relation& Database::GetRelation(std::string relName) {
    return relations[relName];
}