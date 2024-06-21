#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class TreeNode {
public:
    int val;
    vector<TreeNode*> children;

    TreeNode(int x) : val(x) {}
};

bool areIsomorphic(TreeNode* root1, TreeNode* root2, unordered_map<string, bool>& memo);

string treeStructure(TreeNode* node, unordered_map<string, bool>& memo) {
    if (!node) return "NULL";

    vector<string> childStructures;
    for (auto child : node->children) {
        childStructures.push_back(treeStructure(child, memo));
    }
    
    sort(childStructures.begin(), childStructures.end());

    string structure = "(" + to_string(node->val);
    for (const auto& cs : childStructures) {
        structure += cs;
    }
    structure += ")";

    memo[structure] = true;
    return structure;
}

bool areIsomorphic(TreeNode* root1, TreeNode* root2) {
    unordered_map<string, bool> memo;
    return areIsomorphic(root1, root2, memo);
}

bool areIsomorphic(TreeNode* root1, TreeNode* root2, unordered_map<string, bool>& memo) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    if (root1->children.size() != root2->children.size()) return false;

    string structure1 = treeStructure(root1, memo);
    string structure2 = treeStructure(root2, memo);

    return structure1 == structure2;
}

int main() {
    TreeNode* root1 = new TreeNode(1);
    TreeNode* node2_1 = new TreeNode(2);
    TreeNode* node3_1 = new TreeNode(3);
    TreeNode* node4_1 = new TreeNode(4);
    TreeNode* node5_1 = new TreeNode(5);
    TreeNode* node6_1 = new TreeNode(6);
    TreeNode* node7_1 = new TreeNode(7);

    root1->children.push_back(node2_1);
    root1->children.push_back(node3_1);
    node2_1->children.push_back(node4_1);
    node2_1->children.push_back(node5_1);
    node3_1->children.push_back(node6_1);
    node3_1->children.push_back(node7_1);

    TreeNode* root2 = new TreeNode(1);
    TreeNode* node2_2 = new TreeNode(3);
    TreeNode* node3_2 = new TreeNode(2);
    TreeNode* node4_2 = new TreeNode(6);
    TreeNode* node5_2 = new TreeNode(7);
    TreeNode* node6_2 = new TreeNode(4);
    TreeNode* node7_2 = new TreeNode(5);

    root2->children.push_back(node2_2);
    root2->children.push_back(node3_2);
    node2_2->children.push_back(node4_2);
    node2_2->children.push_back(node5_2);
    node3_2->children.push_back(node6_2);
    node3_2->children.push_back(node7_2);

    if (areIsomorphic(root1, root2)) {
        cout << "The trees are isomorphic." << endl;
    } else {
        cout << "The trees are not isomorphic." << endl;
    }


    return 0;
}
