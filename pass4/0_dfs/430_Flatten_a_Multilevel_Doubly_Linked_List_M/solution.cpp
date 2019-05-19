/*
 * 430. Flatten a Multilevel Doubly Linked List
 *
 * You are given a doubly linked list which in addition to the next and previous pointers, it could have a child pointer, 
 * which may or may not point to a separate doubly linked list. These child lists may have one or more children of their 
 * own, and so on, to produce a multilevel data structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. 
You are given the head of the first level of the list.

Example:

Input:
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL

Output:
1-2-3-7-8-11-12-9-10-4-5-6-NULL


Explanation for the above example:

Given the following multilevel doubly linked list:

We should return the following flattened doubly linked list:
 * */

#include <stack>
#include <iostream>

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};

class Solution {
public: 

    Node* flatten(Node* head) {
        dfs(head);
        return head;
    }
    Node* dfs(Node* head) {
        Node* p = head, *prev = nullptr;
        while (p && !p->child) {
            prev = p;
            p = p->next;
        }
        if (p) {
            Node* tmp = p->next;
            p->next = p->child;
            p->next->prev = p;
            p->child = nullptr;
            p = p->next;
            Node* tail = dfs(p);
            tail->next = tmp;
            tmp->prev = tail;
        }
        return prev;
    }
};


void print(Node* n) {
    std::cout << "Node: ";
    Node* prev = nullptr;
    while (n) {
        std::cout << n->val << "->";
        assert(n->child == nullptr);
        prev = n;
        n = n->next;
        if (n) assert(n->prev == prev);
    }
    std::cout << "null" << std::endl;
}
/*
 *   
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL
 * */
int main() {
#if 1
    Node* head = new Node(1, nullptr, nullptr, nullptr);
    head->next = new Node(2, nullptr, nullptr, nullptr);
    head->next->prev = head;
    head->next->next = new Node(3, nullptr, nullptr, nullptr);
    head->next->next->prev = head->next;

    Node* p1 = new Node(7, nullptr, nullptr, nullptr);
    head->next->next->child = p1;
    p1->next = new Node(8, nullptr, nullptr, nullptr);
    p1->next->prev = p1;
    p1->next->next = new Node(9, nullptr, nullptr, nullptr);
    p1->next->next->prev = p1->next;
    p1->next->next->next = new Node(10, nullptr, nullptr, nullptr);
    p1->next->next->next->prev = p1->next->next;

    p1->next->child = new Node(11, nullptr, nullptr, nullptr);
    p1->next->child->next = new Node(12, nullptr, nullptr, nullptr);
    p1->next->child->next->prev = p1->next->child;

    Node* p2 = new Node(4, nullptr, nullptr, nullptr);
    head->next->next->next = p2;
    p2->prev = head->next->next;
    p2->next = new Node(5, nullptr, nullptr, nullptr);
    p2->next->prev = p2;
    p2->next->next = new Node(6, nullptr, nullptr, nullptr);
    p2->next->next->prev = p2->next;
#endif
    Solution s;
    Node* out = s.flatten(head);
    print(out);
    return 1;
}
