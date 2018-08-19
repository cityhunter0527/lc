/*
 * 92. Reverse Linked List II
 * 
 * Reverse a linked list from position m to n. Do it in-place and in one-pass.
 *
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 *
 * return 1->4->3->2->5->NULL.
 *
 * Note:
 * Given m, n satisfy the following condition:
 * 1 <= m <= n <= length of list.
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (m == n) return head;
        int cnt = 1;
        ListNode* savedHead = head;
        ListNode* p = head, *lastNonReverseNode = nullptr, *tmp = nullptr;
        while (p && (cnt < m)) {
            cnt++;
            lastNonReverseNode = p; 
            p = p->next; 
        }
        ListNode* newHead = nullptr, **lastNodesNextInReversedList = &p->next;
        while (p && cnt <=n ) {
            cnt++;
            tmp = p->next;
            p->next = newHead;
            newHead = p;
            p = tmp;
        }
        
        *lastNodesNextInReversedList = p;  // handle tail

        if (m == 1) savedHead = newHead;   // handle head
        else lastNonReverseNode->next = newHead;
        return savedHead;
    }
};

int main () {
    ListNode* r = new ListNode(1);
    r->next = new ListNode(2);
    r->next->next = new ListNode(3);
    r->next->next->next = new ListNode(4);
    r->next->next->next->next = new ListNode(5);
    Solution s;
    ListNode* h = s.reverseBetween(r, 3, 4);
    while (h) {
        cout << h->val << ",";
        h = h->next;
    }
    cout << endl;
    return 1;
}
