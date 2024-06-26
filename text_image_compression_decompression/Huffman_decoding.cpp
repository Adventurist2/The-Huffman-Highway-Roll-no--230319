#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <bitset>
#include <fstream>

using namespace std;

// A Huffman tree node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Compare class for priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Iterate until the heap contains only one node
    while (minHeap.size() != 1) {
        // Remove the two nodes of highest priority (lowest frequency)
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();

        // Create a new internal node with these two nodes as children
        Node *sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;

        // Add the new node to the min-heap
        minHeap.push(sum);
    }

    // The remaining node is the root node
    return minHeap.top();
}

// Function to decode the encoded string using the Huffman tree
string decodeString(Node* root, const string& str) {
    string result;
    Node* current = root;
    for (char bit : str) {
        if (bit == '0') current = current->left;
        else current = current->right;

        // If leaf node is reached
        if (!current->left && !current->right) {
            result += current->ch;
            current = root;
        }
    }
    return result;
}

// Function to read the encoded data from the file
string readEncodedData(ifstream& infile) {
    string encodedData;
    char ch;
    while (infile.get(ch)) {
        encodedData += bitset<8>(ch).to_string();
    }
    return encodedData;
}

int main() {
    // Initialize the frequency map with the provided values
    unordered_map<char, int> freqMap = {
        {'k', 2}, {'j', 1}, {'p', 8}, {'x', 1}, {'K', 1}, {'.', 3}, {'h', 7},
        {'c', 4}, {'e', 17}, {'d', 7}, {'y', 2}, {'C', 1}, {'o', 16}, {'n', 8},
        {'a', 6}, {'w', 1}, {' ', 29}, {'g', 6}, {'t', 14}, {'r', 7}, {'u', 6},
        {'l', 4}, {'i', 5}, {'s', 5}, {'I', 1}, {'f', 2}, {',', 1}
    };

    // Build the Huffman tree
    Node* root = buildHuffmanTree(freqMap);

    // Read the encoded data from the file
    ifstream infile("compressed.txt", ios::binary);
    if (!infile) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    string encodedData = readEncodedData(infile);
    infile.close();

    // Decode the encoded data
    string decodedString = decodeString(root, encodedData);

    // Write the decoded data to the output file
    ofstream outfile("decompressed.txt");
    outfile << decodedString;
    outfile.close();

    cout << "File decompressed successfully." << endl;
    return 0;
}
