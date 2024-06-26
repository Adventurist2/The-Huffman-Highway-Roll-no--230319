#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <bitset>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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

// Function to generate Huffman codes from the Huffman tree
void generateHuffmanCodes(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCode);
    generateHuffmanCodes(root->right, str + "1", huffmanCode);
}

// Function to encode the image data
string encodeImageData(const Mat& img, unordered_map<char, string>& huffmanCode) {
    string encodedData = "";
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            encodedData += huffmanCode[img.at<uchar>(i, j)];
        }
    }
    return encodedData;
}

int main() {
    // Load the input image (grayscale)
    Mat img = imread("input.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Error loading image" << endl;
        return 1;
    }

    // Build the frequency table
    unordered_map<char, int> freqMap;
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            freqMap[img.at<uchar>(i, j)]++;
        }
    }

    // Build the Huffman tree
    Node* root = buildHuffmanTree(freqMap);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    // Encode the image data
    string encodedData = encodeImageData(img, huffmanCode);

    // Write the frequency table and encoded data to a file
    ofstream outfile("compressed.bin", ios::binary);
    int size = freqMap.size();
    outfile.write((char*)&size, sizeof(size));
    for (auto& pair : freqMap) {
        outfile.write((char*)&pair.first, sizeof(pair.first));
        outfile.write((char*)&pair.second, sizeof(pair.second));
    }

    // Write the encoded data
    for (size_t i = 0; i < encodedData.size(); i += 8) {
        bitset<8> bits(encodedData.substr(i, 8));
        unsigned char byte = static_cast<unsigned char>(bits.to_ulong());
        outfile.write((char*)&byte, sizeof(byte));
    }
    outfile.close();

    cout << "Image compressed successfully." << endl;
    return 0;
}
