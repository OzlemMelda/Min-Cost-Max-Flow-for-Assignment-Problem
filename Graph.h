#ifndef GRAPH_H
#include <iostream>
#include <vector>

using namespace std;

class Graph {

private:

    int unitCost = -1; // This cost will be assigned to all edges (for gain)
    const int M = 10000 * 10000;

public:
    
    vector<vector<int>> voltage;
    Graph(vector<vector<int>> voltage) {
        this->voltage = voltage;
    }
    int assignment();
};

#endif //GRAPH_H