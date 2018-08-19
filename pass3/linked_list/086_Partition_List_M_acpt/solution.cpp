/*
 * 86. Partition List
 *
 * Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in each of the two partitions.
 *
 * For example,
 * Given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->4->3->5.
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
    ListNode* partition(ListNode* head, int x) {
        if (!head) return nullptr;
        ListNode* headPartL = nullptr, *headPartR = nullptr, **tailPartL = nullptr, **tailPartR = nullptr;
        while (head) {
            ListNode* savedNext = head->next;
            if (head->val < x) {
                if (headPartL == nullptr) { // <<< first element < x
                    headPartL = head;
                    headPartL->next = nullptr;
                    tailPartL = &(headPartL->next);
                } else {                    // <<< insert to tail of left part
                    *tailPartL = head;
                    (*tailPartL)->next = nullptr;
                    tailPartL = &((*tailPartL)->next);
                }
            } else {
                if (headPartR == nullptr) { // <<< first element >= x
                    headPartR = head;
                    headPartR->next = nullptr;
                    tailPartR = &(headPartR->next);
                } else {                    // <<< insert to tail of right part
                    *tailPartR = head;
                    (*tailPartR)->next = nullptr;
                    tailPartR = &((*tailPartR)->next);
                }
            }
            head = savedNext;
        }
        if (tailPartL) *tailPartL = headPartR;

        return headPartL ? headPartL : headPartR;
    }
};

int main() {
    ListNode* r = new ListNode(1);
#if 0
    r->next = new ListNode(4);
    r->next->next = new ListNode(3);
    r->next->next->next = new ListNode(2);
    r->next->next->next->next = new ListNode(5);
    r->next->next->next->next->next = new ListNode(2);
#endif
    Solution s;
    ListNode* h = s.partition(r, 0);
    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;

    return 1;
}
