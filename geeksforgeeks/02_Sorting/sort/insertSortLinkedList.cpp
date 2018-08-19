/*
 * http://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/
 *
 * 1) Create an empty sorted (or result) list
 * 2) Traverse the given list, do following for every node.
 * ......a) Insert current node in sorted way in sorted or result list.
 * 3) Change head of given linked list to head of sorted (or result) list.
 * */
#include <iostream>
#include <assert.h>
using namespace std;
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
private: 
    // insert n to head
    void sortedInsert(ListNode** head, ListNode* n) {
        assert(n->next == nullptr);
        if (n == nullptr) return;
        if (*head == nullptr) { *head = n; return; }
        if ((*head)->val > n->val) {
            n->next = *head; 
            *head = n; 
            return;
        }
        ListNode* p = *head, *pp = nullptr;
        while (p) {
            if (p->val < n->val) { // <<< move forward until we got the position to insert n
                pp = p;
                p = p->next;
            } else {               // <<< do the insertion
                pp->next = n;
                n->next = p;
                return;
            }
        }
        if (p == nullptr) pp->next = n;
        return;
    }
public:
    ListNode* insertionSort(ListNode* head) {
        if (head == nullptr) return nullptr;
        ListNode* dummyNode = new ListNode(1);
        ListNode* p = head;
        while (p) {
            ListNode* tmp = p->next;
            p->next = nullptr;
            sortedInsert(&(dummyNode->next), p);
            p = tmp;
        }
        return dummyNode->next;
    }
};

int main () {
    ListNode* r = new ListNode(5);
    r->next = new ListNode(4);
    r->next->next = new ListNode(1);
    r->next->next->next = new ListNode(2);
    r->next->next->next->next = new ListNode(6);
    r->next->next->next->next->next = new ListNode(3);
    r->next->next->next->next->next->next = new ListNode(7);
    r->next->next->next->next->next->next->next = new ListNode(8);

    Solution s;
    ListNode* h = s.insertionSort(r);
    while (h) {
        cout << h->val << "->";
        h = h->next;
    }
    cout << "nullptr" << endl;
    return 0;
}

