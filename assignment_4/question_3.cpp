#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int x) : data(x), next(nullptr) {}
};

bool check_palindrome(struct Node* head)
{
    vector<int> v1;
    struct Node* ptr = head;
    while(ptr != nullptr){
        v1.push_back(ptr->data);
        ptr = ptr->next;
    }
    vector<int> v2(v1);
    reverse(v2.begin(), v2.end());
    return v1.size() == v2.size() && std::equal(v1.begin(), v1.end(), v2.begin());
}

Node* createLinkedList(int arr[], int n) {
    if (n == 0) {
        return nullptr;
    }
    Node* head = new Node(arr[0]);
    Node* current = head;
    for (int i = 1; i < n; ++i) {
        current->next = new Node(arr[i]);
        current = current->next;
    }
    return head;
}

int main(){
    int arr1[] = {1, 2, 3, 2, 1};
    int arr2[] = {1, 2, 3, 4, 5};

    Node* list1 = createLinkedList(arr1, 5);
    Node* list2 = createLinkedList(arr2, 5);

    cout << "List 1 is " << (check_palindrome(list1) ? "a palindrome" : "not a palindrome") << endl;
    cout << "List 2 is " << (check_palindrome(list2) ? "a palindrome" : "not a palindrome") << endl;

    return 0;
}
