#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
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

    void traversal(Node* head) {
        Node* ptr = head;
        while (ptr != nullptr) {
            cout << ptr->data << " -> ";
            ptr = ptr->next;
        }
        cout << "Null" << endl;
    }

    Node* rotateRight(Node* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }

        int length = 1;
        Node* tail = head;
        while (tail->next != nullptr) {
            length++;
            tail = tail->next;
        }

        k = k % length;
        if (k == 0) {
            return head;
        }

        int stepsToNewHead = length - k;
        Node* newTail = head;
        for (int i = 1; i < stepsToNewHead; i++) {
            newTail = newTail->next;
        }

        Node* newHead = newTail->next;
        newTail->next = nullptr;
        tail->next = head;

        return newHead;
    }
};

int main() {
    Node list(0); 

    int arr[] = {1, 2, 3, 4, 5};
    Node* head = list.createLinkedList(arr, 5);
    int k;
    cout<<"enter value of k"<<endl;
    cin>>k;
    list.traversal(head);

    head = list.rotateRight(head, k);

    list.traversal(head);

    return 0;
}
