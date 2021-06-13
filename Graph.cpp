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