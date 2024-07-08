#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int v, const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (graph[path[pos - 1]][v] == 0) {
        return false;
    }
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }
    return true;
}

bool hamiltonianPathUtil(const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (pos == graph.size()) {
        return true;
    }
    for (int v = 1; v < graph.size(); v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;
            if (hamiltonianPathUtil(graph, path, pos + 1)) {
                return true;
            }
            path[pos] = -1;
        }
    }
    return false;
}

bool hamiltonianPath(const vector<vector<int>>& graph) {
    vector<int> path(graph.size(), -1);
    path[0] = 0;
    if (!hamiltonianPathUtil(graph, path, 1)) {
        return false;
    }
    return true;
}

bool hamiltonianCycleUtil(const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (pos == graph.size()) {
        return graph[path[pos - 1]][path[0]] == 1;
    }
    for (int v = 1; v < graph.size(); v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;
            if (hamiltonianCycleUtil(graph, path, pos + 1)) {
                return true;
            }
            path[pos] = -1;
        }
    }
    return false;
}

bool hamiltonianCycle(const vector<vector<int>>& graph) {
    vector<int> path(graph.size(), -1);
    path[0] = 0;
    if (!hamiltonianCycleUtil(graph, path, 1)) {
        return false;
    }
    return true;
}

int main() {
    int V = 5;
    vector<vector<int>> graph = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };

    if (hamiltonianPath(graph)) {
        cout << "Hamiltonian Path exists" << endl;
    } else {
        cout << "No Hamiltonian Path exists" << endl;
    }

    if (hamiltonianCycle(graph)) {
        cout << "Hamiltonian Cycle exists" << endl;
    } else {
        cout << "No Hamiltonian Cycle exists" << endl;
    }

    return 0;
}
