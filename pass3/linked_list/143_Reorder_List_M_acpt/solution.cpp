/*
 * 143. Reorder List
 *
 * Given a singly linked list L: L0->L1->...->Ln-1->Ln,
 * reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...
 *
 * You must do this in-place without altering the nodes' values.
 *
 * For example,
 * Given {1,2,3,4}, reorder it to {1,4,2,3}.
 * */

#include <iostream>
using namespace std;

/** *  * Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next || !head->next->next) return;
        ListNode* a = nullptr, *b = nullptr;
        frontBackSplit(head, a, b);
        b = reverse(b);
        head = merge(a,b);
        return;
    }
private:
    void frontBackSplit(ListNode* head, ListNode*& a, ListNode*& b) {
        if (!head) {
            a = nullptr; b = nullptr;
            return;
        }
        ListNode* slow = head, *fast = head->next;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        slow->next = nullptr;
        slow = head;
        a = slow;
        b = fast;
        return;
    }
    ListNode* reverse(ListNode* l) {
        ListNode* h = nullptr, *tmp = nullptr;
        while (l) {
            tmp = l->next;
            l->next = h;
            h = l;
            l = tmp;
        }
        return h;
    }
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode *p, *savedHead = a;
        while (a && b) {
            p = a->next;
            a->next = b;
            a = b->next;
            b->next = p;
            b = a;
            a = p;
        }
        
        return savedHead;
    }
};

int main() {
    ListNode* h = new ListNode(1);
    h->next = new ListNode(2);
    h->next->next = new ListNode(3);
    h->next->next->next = new ListNode(4);
    //h->next->next->next->next = new ListNode(5);

    Solution s;
    s.reorderList(h);
    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;
    return 1;
}
