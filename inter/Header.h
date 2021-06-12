#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
#include <sstream>

class Header {
private:
    std::vector<std::string> attributes;
public:
    Header() : attributes() {}
    explicit Header(std::vector<std::string>& atts) { attributes = atts; }
    ~Header() = default;

    // Mutators / Accessors
    void Add (const std::string value) { attributes.push_back(value); }
    void Add (std::vector<std::string>& atts) { for (std::string val : atts) attributes.push_back(val); }
    size_t Size() { return attributes.size(); }
    std::vector<std::string> GetAtts() { return attributes; }
    std::string operator[](size_t& index) { return attributes[index]; }
};
#endif // HEADER_H
