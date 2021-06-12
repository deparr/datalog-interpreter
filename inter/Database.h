#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <sstream>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation> relations;
public:
    Database() : relations() {}
    ~Database() = default;

    // Mutators
    void AddRelation(Relation& newRelation);
    void MatchAddTuple(std::string relName, Tuple& tuple);

    // Accessors
    Relation& GetRelation(std::string relName);

};
#endif // DATABASE_H
