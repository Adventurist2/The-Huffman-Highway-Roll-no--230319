#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void buildParentMap(TreeNode* root, unordered_map<int, TreeNode*>& parentMap, TreeNode* parent) {
    if (!root) return;
    parentMap[root->val] = parent;
    buildParentMap(root->left, parentMap, root);
    buildParentMap(root->right, parentMap, root);
}

TreeNode* getLCA(int u, int v, unordered_map<int, TreeNode*>& parentMap) {
    unordered_map<int, bool> visited;
    while (u != -1) {
        visited[u] = true;
        u = parentMap[u] ? parentMap[u]->val : -1;
    }
    while (v != -1) {
        if (visited[v]) return new TreeNode(v);
        v = parentMap[v] ? parentMap[v]->val : -1;
    }
    return nullptr;
}

void DFS(TreeNode* root, int target, vector<int>& pathValues, int& sum, int& maxVal, int& minVal) {
    if (!root) return;
    
    // Update path values
    pathValues.push_back(root->val);
    sum += root->val;
    maxVal = max(maxVal, root->val);
    minVal = min(minVal, root->val);
    
    // Recursively search in left and right subtrees
    if (root->val == target) return;
    if (root->left) {
        DFS(root->left, target, pathValues, sum, maxVal, minVal);
        if (pathValues.back() == target) return; // Found in left subtree
    }
    if (root->right) {
        DFS(root->right, target, pathValues, sum, maxVal, minVal);
        if (pathValues.back() == target) return; // Found in right subtree
    }
    
    // Backtrack
    pathValues.pop_back();
    sum -= root->val;
}

vector<int> query(int u, int v, TreeNode* root, unordered_map<int, TreeNode*>& parentMap) {
    TreeNode* lca = getLCA(u, v, parentMap);
    int lcaVal = lca->val;
    
    vector<int> pathValues;
    int sum = 0, maxVal = INT_MIN, minVal = INT_MAX;
    
    // Calculate path values for node u
    DFS(root, u, pathValues, sum, maxVal, minVal);
    int sumU = sum, maxU = maxVal, minU = minVal;
    
    // Reset variables for node v
    pathValues.clear();
    sum = 0, maxVal = INT_MIN, minVal = INT_MAX;
    
    // Calculate path values for node v
    DFS(root, v, pathValues, sum, maxVal, minVal);
    int sumV = sum, maxV = maxVal, minV = minVal;
    
    // Calculate total sum, max, min values
    int totalSum = sumU + sumV - lcaVal;
    int maxResult = max(max(maxU, maxV), lcaVal);
    int minResult = min(min(minU, minV), lcaVal);
    
    return {totalSum, maxResult, minResult};
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    unordered_map<int, TreeNode*> parentMap;
    buildParentMap(root, parentMap, nullptr);

    vector<pair<int, int>> queries = {{2, 4}, {5, 1}};
    for (auto q : queries) {
        vector<int> res = query(q.first, q.second, root, parentMap);
        cout << "Sum: " << res[0] << ", Max: " << res[1] << ", Min: " << res[2] << endl;
    }

    return 0;
}
