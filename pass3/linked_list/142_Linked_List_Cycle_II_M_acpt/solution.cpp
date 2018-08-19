/*
 * 142. Linked List Cycle II
 *
 * Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
 *
 * Note: Do not modify the linked list.
 *
 * Follow up:
 * Can you solve it without using extra space?
 * */


#include <iostream>
using namespace std;
/** Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head, *slow = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) {
                while (head != slow) {
                    head = head->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};

int main() {
    ListNode* r = new ListNode(1);
    r->next = new ListNode(2);
    r->next->next = new ListNode(3);
    r->next->next->next = new ListNode(4);
    r->next->next->next->next = new ListNode(5);
    r->next->next->next->next->next = new ListNode(6);
    r->next->next->next->next->next->next = new ListNode(7);
    r->next->next->next->next->next->next->next = new ListNode(8);
    r->next->next->next->next->next->next->next->next = new ListNode(9);
    r->next->next->next->next->next->next->next->next->next = new ListNode(10);
    r->next->next->next->next->next->next->next->next->next->next = r->next->next->next->next;

    Solution s;
    ListNode* p = s.detectCycle(r);
    if (p) 
        cout << p->val << endl;
    return 0;
}
