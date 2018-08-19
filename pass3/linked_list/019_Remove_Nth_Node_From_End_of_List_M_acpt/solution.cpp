/*
 * 19. Remove Nth Node From End of List
 * Given a linked list, remove the nth node from the end of list and return its head.
 * 
 * For example,
 *    Given linked list: 1->2->3->4->5, and n = 2.
 * 
 * After removing the second node from the end, the linked list becomes 1->2->3->5.
 * Note:
 * Given n will always be valid.
 * Try to do this in one pass.
 * */

#include <iostream>
#include <vector>
using namespace std;

/** *  * Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> v;
        ListNode* savedHead = head;
        int cnt = 0;
        while (head) {
            v.push_back(head);
            head = head->next;
            cnt++;
        }
        if (cnt == n) return savedHead->next;
        v[cnt-n-1]->next = v[cnt-n]->next;
        return savedHead;
    }
};

int main() {
    ListNode* r = new ListNode(1);
    Solution s;
    ListNode* h = s.removeNthFromEnd(r, 1);
    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;
    return 1;
}
