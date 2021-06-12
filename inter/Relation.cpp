#include "Relation.h"

// Select tuples with given value in the given column
Relation Relation::Select(size_t index, std::string value) {

    Relation newRel = Relation(this->name, this->header);
    for (Tuple t : tuples) {
        if (t.values[index] == value) {
            newRel.AddTuple(t);
        }
    }
    return newRel;
}

// Select tuples with matching values in the given columns
Relation Relation::Select(size_t index, size_t otherIndex) {

    Relation newRel = Relation(this->name, this->header);
    for (Tuple t : tuples) {
        if (t.values[index] == t.values[otherIndex]) {
            newRel.AddTuple(t);
        }
    }
    return newRel;
}

// Create new Relation from the selected columns
Relation Relation::Project(std::vector<size_t>& cols) {

    Header newHead;
    for (size_t& i : cols) {
        newHead.Add(this->header[i]);
    }
    Relation newRel(this->name, newHead);

    for (Tuple t : this->tuples) {
        Tuple newTuple;
        for (size_t& i : cols) {
            newTuple.Add(t.values[i]);
        }
        newRel.AddTuple(newTuple);
    }

    return newRel;
}

// Project by value, used in rule evaluation
Relation Relation::Project(std::vector<std::string>& cols) {

    Header newHead;
    for (std::string val : cols) {
        newHead.Add(val);
    }
    Relation newRel(this->name, newHead);

    /*std::vector<size_t> colIndex;
    for (std::string val : this->GetHeader()) {
        for (size_t i = 0; i < cols.size(); i++) {
            if (val == cols[i]) { colIndex.push_back(i); }
        }
    }*/

    for (Tuple t : this->tuples) {
        Tuple newTuple;
        for (std::string colVal : cols) {
            newTuple.values.push_back(t.values[GetHeaderIndex(colVal, this)]);
        }
        newRel.AddTuple(newTuple);
    }

    return newRel;
}

// Rebuild header using names given in query
Relation Relation::Rename(std::vector<std::string>& atts) {
    return Relation(this->name, Header(atts), this->tuples);
}

// Natural join to be used in rule evaluation, this = lhs
Relation* Relation::Join(Relation* rhs) {
    Header newHead;
    std::vector<std::string> joinCols;

    // Determine which colmuns to join
    for (std::string val : this->GetHeader()) { newHead.Add(val); }

    for (std::string val : rhs->GetHeader()) {
        bool inHeader = false;
        for (std::string headVal : newHead.GetAtts()) {
            if (val == headVal) {
                joinCols.push_back(val);
                inHeader = true;
                break;
            }
        }

        if (!inHeader) newHead.Add(val);
    }

    Relation* relptr = new Relation("empty", newHead);

    // Do natural join if there are common headers
    if (joinCols.size()) {
        for (Tuple lhsRow : this->GetTuples()) {
            for (Tuple rhsRow : rhs->GetTuples()) {

                if (JoinableTuples(lhsRow, rhsRow, rhs, joinCols)) {
                    Tuple newTuple = JoinTuples(lhsRow, rhsRow, rhs);
                    relptr->AddTuple(newTuple);
                }
            }
        }
    }
    // Else do a cartesian product
    else {
        for (Tuple lhsRow : this->GetTuples()) {
            for (Tuple rhsRow : rhs->GetTuples()) {
                Tuple newTuple = lhsRow + rhsRow;
                relptr->AddTuple(newTuple);
            }
        }
    }


    return relptr;
}

bool Relation::JoinableTuples(Tuple& lhs, Tuple& rhs, Relation* rhsRel, std::vector<std::string>& joinCols) {
    for(size_t i = 0; i < joinCols.size(); i++) {
        if (!(lhs.values[GetHeaderIndex(joinCols[i], this)] == rhs.values[GetHeaderIndex(joinCols[i], rhsRel)])) {
            return false;
        }
    }

    return true;
}

Tuple Relation::JoinTuples(Tuple& lhs, Tuple& rhs, Relation* rhsRel) {
    Tuple newTuple = lhs;
    
    std::set<std::string> joinedHeads;
    for (std::string val : this->GetHeader()) joinedHeads.insert(val);

    for (size_t i = 0; i < rhsRel->GetHeaderSize(); i++) {
        if (!joinedHeads.count((*rhsRel)[i])) {
            newTuple.values.push_back(rhs.values[i]);
            joinedHeads.insert((*rhsRel)[i]);
        }
    }

    return newTuple;
}

size_t Relation::GetHeaderIndex(std::string& headToMatch, Relation* relptr) {
    for (size_t i = 0; i < relptr->GetHeader().size(); i++) {
        if (headToMatch == (*relptr)[i]) {
            return i;
        }
    }
    return 0;
}

bool Relation::Union(Relation& dbRel) {
    bool addNewTuple = false;
    for (Tuple t : this->GetTuples()) {
        if (dbRel.DBAddTuple(t)) {
            addNewTuple = true;
            std::cout << "  ";
            for (size_t i = 0; i < dbRel.GetHeaderSize(); i++) {
                std::cout << dbRel[i] << "=" << t.values[i];
                if (i != dbRel.GetHeaderSize()-1) std::cout << ", ";
                else std::cout << std::endl;
            }
        }
    }
 
	return addNewTuple;
}



std::string Relation::ToString() {
    std::ostringstream os;

    // If header has no variables, dont print Tuples
    if (!header.Size()) return os.str();

    for (const Tuple& t : tuples) {
        os << "  ";
        for (size_t i = 0; i < header.Size(); i++) {
            os << header[i] << "=" << t.values[i];
            if (i != header.Size() - 1) os << ", ";
        }
        os << std::endl;
    }

    return os.str();
}


