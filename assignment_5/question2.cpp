#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int minimumCostToMergeFiles(vector<int>& fileSizes) {
    priority_queue<int, vector<int>, greater<int>> minHeap(fileSizes.begin(), fileSizes.end());
    int totalCost = 0;
    
    while (minHeap.size() > 1) {
        int smallest = minHeap.top(); minHeap.pop();
        int secondSmallest = minHeap.top(); minHeap.pop();
        int mergeCost = smallest + secondSmallest;
        totalCost += mergeCost;
        minHeap.push(mergeCost);
    }
    
    return totalCost;
}

int main() {
    vector<int> fileSizes = {4, 3, 2, 6};
    cout << "Minimum Cost = " << minimumCostToMergeFiles(fileSizes) << endl;
    return 0;
}
