#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <sstream>
#include "parser/Rule.h"

class Graph {
private:
    std::set<int> nodes;
    std::map<int, std::set<int> > edges;
    std::string PrintDepencies();

public:
    Graph(std::vector<Rule>& rules);
    ~Graph() = default;


    friend std::ostream& operator<<(std::ostream& os, Graph& graph) {
        os << graph.PrintDepencies();
        return os;
    }

};
#endif  // GRAPH_H