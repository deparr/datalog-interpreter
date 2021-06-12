#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include <vector>
#include <sstream>

struct Tuple {

    // Data members
    std::vector<std::string> values;

    Tuple() : values() {}
    ~Tuple() = default;

    // Mutators
    void Add(const std::string& value) { values.push_back(value);}

    // Operators
    bool operator< (const Tuple& rhs) const {
        return values < rhs.values;
    }

    Tuple operator+ (const Tuple& rhs) {
        Tuple newTuple;
        for (std::string val : this->values) newTuple.values.push_back(val);
        for (std::string val : rhs.values) newTuple.values.push_back(val);
        return newTuple;
    }


    // Output
    std::string ToString() const {
        std::ostringstream os;
        for (std::string val : values) {
            os << val << " ";
        }
        os << std::endl;
        return os.str();
    }
    friend std::ostream& operator<<(std::ostream& os, const Tuple& tuple) {
        os << tuple.ToString();
        return os;
    }
};
#endif // TUPLE_H
