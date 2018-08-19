/*
 * 24. Swap Nodes in Pairs
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 * Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
 * */

#include <iostream>
using namespace std;

/** *  * Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *pp = head, *a, *b, *q = nullptr;
        ListNode *nh = head?(head->next?head->next:head):head;
        // every time the wihle loop go from
        // pp == a->b->(b->next)  
        // to: 
        //       b->a->(b->next) // pp: b->next, q: a
        while ((a = pp) && (b = a->next)) {
            a->next = b->next;
            b->next = a;
            if (q) q->next = b;
            q = a;
            pp = a->next;
        }

        return nh;
    }
};

int main() {
    ListNode* h = new ListNode(1);
    h->next = new ListNode(2);
    h->next->next = new ListNode(3);
    h->next->next->next = new ListNode(4);

    Solution s;
    h = s.swapPairs(h);

    while (h) {
        cout << h->val << "->"; 
        h = h->next;
    }
    cout << endl;
    return 1;
}
