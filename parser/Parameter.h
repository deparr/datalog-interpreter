#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>

class Parameter {
private:
    std::string value;
    int type; // 0 - ID,   1 - STRING
public:
    Parameter(std::string initVal, int type_) : value(initVal), type(type_) {}
    ~Parameter() = default;

    int GetType() const {
        return type;
    }

    friend std::ostream& operator<<(std::ostream& os, Parameter& param) {
        os << param.value;
        return os;
    }

    std::string operator*() { return value; }
};
#endif // PARAMETER_H