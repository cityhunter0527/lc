/*
 * 147. Insertion Sort List
 *
 * Sort a linked list using insertion sort.
 * */

#include <iostream>
#include <assert.h>
using namespace std;

/** *  * Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    // 1) Create an empty sorted (or result) list
    // 2) Traverse the given list, do following for every node.
    // ......a) Insert current node in sorted way in sorted or result list.
    // 3) Change head of given linked list to head of sorted (or result) list.
    ListNode* insertionSortList(ListNode* head) {
        ListNode* sortHead = nullptr, *tmp = nullptr;
        while (head) {
            tmp = head->next;
            head->next = nullptr;
            sortHead = insertSorted(sortHead, head);
            head = tmp;
        }
        return sortHead;
    }
private:
    ListNode* insertSorted(ListNode* h, ListNode*& n) {
        assert(n && (n->next == nullptr));
        if (!h) return n; 
        if (h->val >= n->val) {
            n->next = h; 
            return n;
        }
        ListNode* ph = h, *savedHead = h;
        h = h->next;
        while (h) {
            if (h->val < n->val) { 
                // keep looking
                ph = h;
                h = h->next;
            } else {
                // found
                n->next = h;
                break;
            }
        }
        // either h is null(n should inserted as tail) or found a position to insert n
        ph->next = n;
        return savedHead;
    }
};

int main() {
    ListNode* l1 = new ListNode(9);
    l1->next = new ListNode(3);
    l1->next->next = new ListNode(1);
    l1->next->next->next = new ListNode(7);
    l1->next->next->next->next = new ListNode(2);
    l1->next->next->next->next->next = new ListNode(6);
    l1->next->next->next->next->next->next = new ListNode(8);
    l1->next->next->next->next->next->next->next = new ListNode(5);
    l1->next->next->next->next->next->next->next->next = new ListNode(0);
    l1->next->next->next->next->next->next->next->next->next = new ListNode(4);

    Solution s;
    ListNode* h = s.insertionSortList(l1);
    while (h) {
        cout << h->val << endl;
        h = h->next;
    }
    cout << endl;

    return 1;
}
