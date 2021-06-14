#include "Graph.h"

Graph::Graph(std::vector<Rule>& rules) {
    for (size_t i = 0; i < rules.size(); i++) {
        nodes.insert(i);

        for (size_t j = 0; j < rules[i].Size(); j++) {
            for (size_t k = 0; k < rules.size(); k++) {

                if (*rules[i][j] == *rules[k].GetHeadPred()) {
                    edges[i].insert(k);
                }
            }
        }
    }
}



std::string Graph::PrintDepencies() {
    std::ostringstream os;

    for (int node : nodes) {
        os << "R" << node << ":";

        std::set<int>::iterator it = edges[node].begin();
        while(it != edges[node].end()) {
            os << "R" << *it++;
            if (it != edges[node].end()) {
                os << ",";
            }
        }

        os << std::endl;
    }

    os << std::endl;
    return os.str();
}

void Graph::AddEdge(int node, int depNode) {
    this->edges[node].insert(depNode);
    return;
}

Graph Graph::Reverse() {
    Graph rev(this->nodes);

    for (int oldDependent : this->nodes) {
        for (int newDependent : this->edges[oldDependent]) {
            rev.AddEdge(newDependent, oldDependent);
        }
    }

    return rev;
}

bool Graph::CheckDependence(int node, int depNode) { return edges[node].count(depNode); }


// DFS ALGORITHIM USED ON REVERSE GRAPH TO FIND POSTORDER
void Graph::dfsForest(std::deque<int>& postorder) {
    std::map<int, bool> marked;
    for (int node : this->nodes) {
        if (!marked[node]) {
            DFS(node, marked, postorder);
        }
    }

    return;
}

void Graph::DFS(int& node, std::map<int, bool>& marked, std::deque<int>& postorder) {
    marked[node] = true;

    for (int nextNode : this->edges[node]) {
        if (!marked[nextNode]) DFS(nextNode, marked, postorder);
    }
    
    postorder.push_back(node);

    return;
}


// DFS FOREST USED ON ORIGINAL GRAPH TO FIND SCCs
void Graph::dfsForest(std::deque<int>& postorder, std::vector<std::set<int>>& SCCs) {
    std::map<int, bool> marked;
    std::deque<int>::reverse_iterator node = postorder.rbegin();

    while (node != postorder.rend()) {
        if (!marked[*node]) {
            std::set<int> newSCC;
            DFS(*node, marked, newSCC);
            SCCs.push_back(newSCC);
        }
        node++;
    }
    return;
}

void Graph::DFS(int& node, std::map<int, bool>& marked, std::set<int>& scc) {
    marked[node] = true;

    for (int nextNode : this->edges[node]) {
        if (!marked[nextNode]) DFS(nextNode, marked, scc);
    }

    scc.insert(node);

    return;
}