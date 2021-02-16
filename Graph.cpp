#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int Graph::assignment() {

    for (int i = 0; i < voltage.size(); i++)
    {
        for (int j = 0; j < voltage[i].size(); j++) {
            voltage[i][j] = voltage[i][j] * unitCost;
        }
    }

    int n = voltage.size(); // Number of cables
    int verticeNum = n * 2 + 2; // Added 2 (source and sink)
    int s = verticeNum - 2, t = verticeNum - 1;
    vector<vector<int>> assignment(verticeNum, vector<int>(verticeNum));
    int totalCost = 0;

    while (true) {
        vector<int> cost(verticeNum, M);
        vector<int> parent(verticeNum);
        vector<bool> inqueue(verticeNum, false);
        queue<int> q;
        cost[s] = 0;
        parent[s] = -1;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            inqueue[v] = false;
            if (v == s) {
                for (int i = 0; i < n; ++i) {
                    if (assignment[s][i] == 0) {
                        cost[i] = 0;
                        parent[i] = s;
                        q.push(i);
                        inqueue[i] = true;
                    }
                }
            }
            else {
                if (v < n) {
                    for (int i = n; i < n + n; ++i) {
                        if (assignment[v][i] < 1 && cost[i] > cost[v] + voltage[v][i - n]) {
                            cost[i] = cost[v] + voltage[v][i - n];
                            parent[i] = v;
                            if (!inqueue[i]) {
                                q.push(i);
                                inqueue[i] = true;
                            }
                        }
                    }
                }
                else {
                    for (int i = 0; i < n; ++i) {
                        if (assignment[v][i] < 0 && cost[i] > cost[v] - voltage[i][v - n]) {
                            cost[i] = cost[v] - voltage[i][v - n];
                            parent[i] = v;
                            if (!inqueue[i]) {
                                q.push(i);
                                inqueue[i] = true;
                            }
                        }
                    }
                }
            }
        }

        int currentCost = M;

        for (int i = n; i < n + n; ++i) {
            if (assignment[i][t] == 0 && cost[i] < currentCost) {
                currentCost = cost[i];
                parent[t] = i;
            }
        }

        if (currentCost == M)
            break;

        totalCost += currentCost;

        for (int current = t; current != -1; current = parent[current]) {
            int previous = parent[current];
            if (previous != -1)
                assignment[current][previous] = -(assignment[previous][current] = 1);
        }
    }

    /*for (int i = 0; i < assignment.size(); ++i) {
        for (int j = 0; j < assignment.size(); ++j) {
            cout << assignment[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;*/

    return totalCost/unitCost;
}