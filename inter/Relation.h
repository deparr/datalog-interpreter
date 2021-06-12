#ifndef RELATION_H
#define RELATION_H

#include <set>
#include "Tuple.h"
#include "Header.h"


#include <iostream>

class Relation {
private:
    std::string name;
    Header header;
    std::set<Tuple> tuples;

    bool JoinableTuples(Tuple& lhs, Tuple& rhs, Relation* rhsRel, std::vector<std::string>& joinCols);
    Tuple JoinTuples(Tuple& lhs, Tuple& rhs, Relation* rhsRel);

public:
    Relation(std::string name_) : name(name_), header(), tuples() {}
    Relation(std::string name_, Header header_) : name(name_), header(header_) {}
    Relation(std::string name_, Header header_, std::set<Tuple>& tuples_) :
                                name(name_), header(header_), tuples(tuples_) {}
    Relation() : name(), header(), tuples() {}

    ~Relation() = default;

    // Mutators
    void AddToHeader(const std::string& value) { header.Add(value); }
    bool DBAddTuple(Tuple& newTuple) { return tuples.insert(newTuple).second; }
    void AddTuple(Tuple& newTuple) { tuples.insert(newTuple); }

    // Accessors
    std::string GetName() { return name; }
    size_t ListSize() { return tuples.size(); }
    size_t GetHeaderSize() { return header.Size(); }
    bool Empty() { return tuples.empty(); }
    std::vector<std::string> GetHeader() { return header.GetAtts(); }
    std::set<Tuple>& GetTuples() { return tuples; }
    size_t GetHeaderIndex(std::string& headToMatch, Relation* relptr);

    std::string operator[](size_t index) { return header[index]; }


    // Output
    std::string ToString();
    friend std::ostream& operator<<(std::ostream& os, Relation& rel) {
        os << rel.ToString();
        return os;
    }

    // Relational operations
    Relation Select(size_t index, std::string paramName);
    Relation Select(size_t index, size_t otherIndex);
    Relation Project(std::vector<size_t>& cols);
    Relation Project(std::vector<std::string>& cols);
    Relation Rename(std::vector<std::string>& atts);

	Relation* Join(Relation* rhs);
	bool Union(Relation& dbRel);
};
#endif // RELATION_H
