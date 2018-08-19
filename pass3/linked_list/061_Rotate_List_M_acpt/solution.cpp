/*
 * 61. Rotate List
 *
 * Given a list, rotate the list to the right by k places, where k is non-negative.
 *
 *
 * Example:
 *
 * Given 1->2->3->4->5->NULL and k = 2,
 *
 * return 4->5->1->2->3->NULL.
 * */

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr;
        int len = 0; 
        ListNode* p = head, *savedTail = nullptr;
        while (p) {
            len++;
            savedTail = p;
            p = p->next;
        }
        k = k%len; 
        if (len == k) return head;

        p = head;
        int i = 0;
        while (i < len-k) {
            p = p->next;
            i++;
        }
        savedTail->next = head;
        head = p->next;
        p->next = nullptr;
        return head;
    }
};

int main() {
    ListNode* r = new ListNode(1);
    r->next = new ListNode(2);
    r->next->next = new ListNode(3);
    r->next->next->next = new ListNode(4);
    r->next->next->next->next = new ListNode(5);

    Solution s;
    ListNode* h = s.rotateRight(r, 4);

    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;
    return 0;
}
