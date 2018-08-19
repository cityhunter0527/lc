#include <iostream>
using namespace std;
struct Node {
    int   val;
    Node* next;
    Node(int x): val(x), next(nullptr) {}
};

Node* ReverseLinkedList(Node* h) {
    Node* p = h, *pp = nullptr, *q;
    while (p) {
        q = p->next;
        p->next = pp;
        pp = p;
        p = q;
    }
    return pp;
}

int main() {
    Node* h = new Node(1);
    h->next = new Node(2);
    h->next->next = new Node(3);
    h->next->next->next = new Node(4);
    h->next->next->next->next = new Node(5); 
    h = ReverseLinkedList(h);

    return 1;
}

