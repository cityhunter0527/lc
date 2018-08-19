#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
};

Node* Merge (Node* head1, Node* head2) {
    Node helperNode;
    helperNode.next = nullptr;
    
    Node *tail = &helperNode;

    while (1) {
        if (!head1) {
            tail->next = head2; 
            break;
        }
        if (!head2) { 
            tail->next = head1;
            break;
        }

        if (head1->data <= head2->data) {
            tail->next = head1;
            tail = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            tail = head2;
            head2 = head2->next;
        }

        tail->next = nullptr;
    }
    return helperNode.next;
}

int main() {
    Node n1, n2, n3, n4, n5, n6, n7;
    n1.data = 1; n1.next = &n3;
    n2.data = 2; n2.next = &n4;
    n3.data = 3; n3.next = &n5;
    n4.data = 5; n4.next = &n6;
    n5.data = 5; n5.next = &n7;
    n6.data = 5; n6.next = nullptr;
    n7.data = 7; n7.next = nullptr;
    Node *newHead = Merge(&n1, &n2);
    while (newHead) {
        cout << newHead->data << endl;
        newHead = newHead->next;
    }
    cout << endl;
    return 1;
}

