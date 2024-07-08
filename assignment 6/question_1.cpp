#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void dfs(unordered_map<int, vector<int>>& graph, int start, int end, vector<int>& path, vector<vector<int>>& all_paths) {
    path.push_back(start);
    if (start == end) {
        all_paths.push_back(path);
    } else {
        for (int neighbor : graph[start]) {
            if (find(path.begin(), path.end(), neighbor) == path.end()) {
                dfs(graph, neighbor, end, path, all_paths);
            }
        }
    }
    path.pop_back();
}

vector<vector<int>> findAllPaths(unordered_map<int, vector<int>>& graph, int start, int end) {
    vector<vector<int>> all_paths;
    vector<int> path;
    dfs(graph, start, end, path, all_paths);
    return all_paths;
}

int main() {
    unordered_map<int, vector<int>> graph;
    vector<pair<int, int>> edges = {
        {1, 2},
        {1, 3},
        {2, 3},
        {2, 4},
        {3, 4},
        {4, 5}
    };
    for (auto& edge : edges) {
        graph[edge.first].push_back(edge.second);
    }
    int start_node = 1;
    int end_node = 4;
    vector<vector<int>> all_paths = findAllPaths(graph, start_node, end_node);
    for (auto& path : all_paths) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}
