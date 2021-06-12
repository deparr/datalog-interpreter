#include "Predicate.h"

std::string Predicate::ToString() {
    std::ostringstream os;

    // ID(PARAM, ..., PARAM)
    os <<  mainID << "(";
    os << *parameterList[0];
    for (size_t i = 1; i < parameterList.size(); i++) {
        os << "," << *parameterList[i];
    }
    os << ")";
    return os.str();
}