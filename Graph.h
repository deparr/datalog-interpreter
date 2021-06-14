#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <deque>
#include <sstream>
#include "parser/Rule.h"

class Graph {
private:
    std::set<int> nodes;
    std::map<int, std::set<int> > edges;
    std::string PrintDepencies();

    void DFS(int& node, std::map<int, bool>& marked, std::deque<int>& postorder);
    void DFS(int& node, std::map<int, bool>& marked, std::set<int>& scc);

public:
    Graph(std::vector<Rule>& rules);
    Graph(std::set<int>& nodes_) : nodes(nodes_), edges() {}
    ~Graph() = default;


    Graph Reverse();
    void AddEdge(int node, int depNode);
    bool CheckDependence(int node, int depNode);

    void dfsForest(std::deque<int>& postorder);
    void dfsForest(std::deque<int>& postorder, std::vector<std::set<int>>& SCCs);


    friend std::ostream& operator<<(std::ostream& os, Graph& graph) {
        os << graph.PrintDepencies();
        return os;
    }

};
#endif  // GRAPH_H