#include <bits/stdc++.h>
using namespace std;

int knapsack(int N, int W, vector<int>& weights, vector<int>& values, vector<int>& dependencies, vector<int>& categories, vector<int>& limits) {
    // Initialize DP array
    vector<int> dp(W + 1, 0);

    // To handle dependencies, we need to preprocess and order the items based on their dependencies
    vector<vector<int>> graph(N);
    vector<int> indegree(N, 0);
    for (int i = 0; i < N; ++i) {
        if (dependencies[i] != -1) {
            graph[dependencies[i]].push_back(i);
            indegree[i]++;
        }
    }

    // Topological sorting to handle dependencies
    queue<int> q;
    for (int i = 0; i < N; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> sorted_items;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        sorted_items.push_back(u);
        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Process items in topologically sorted order
    for (int i : sorted_items) {
        int weight = weights[i];
        int value = values[i];
        int limit = limits[i];
        int category = categories[i];

        for (int k = 1; k <= limit; ++k) {
            for (int w = W; w >= weight; --w) {
                if (dp[w - weight] != -1) {
                    dp[w] = max(dp[w], dp[w - weight] + value);
                }
            }
        }
    }

    // Final result is the maximum value achievable with weight W
    return *max_element(dp.begin(), dp.end());
}

int main() {
    int N, W;
    cin >> N >> W;

    vector<int> weights(N);
    vector<int> values(N);
    vector<int> dependencies(N);
    vector<int> categories(N);
    vector<int> limits(N);

    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> values[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> dependencies[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> categories[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> limits[i];
    }

    int result = knapsack(N, W, weights, values, dependencies, categories, limits);
    cout << "Maximum Knapsack Value: " << result << endl;

    return 0;
}
