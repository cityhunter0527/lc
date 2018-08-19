/*
 * 234. Palindrome Linked List
 *
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
 * */

#include <iostream>
using namespace std;

/*** Definition for singly-linked list. ***/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    // reverse a linked list starting from head;
    // return the new head;
    ListNode* reverseLinkedList(ListNode* head) {
        ListNode *next = nullptr, *prev = nullptr;
        while (head) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
public:
    // O(n) Complexity, 
    // O(1) Space
    //
    // Reverse 2nd half and compare one by one;
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head, *fast = slow;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // slow points to start of 2nd half reversed list
        slow = reverseLinkedList(slow);
        while (slow) {
            if (head->val != slow->val) 
                return false;
            head = head->next;
            slow = slow->next;
        }
        return true;
    }
};

int main() {
#if 1
    ListNode* head = new ListNode(2);
    head->next = new ListNode(3);
    head->next->next = new ListNode(4);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(2);
#endif 
    Solution s;
    bool b = s.isPalindrome(head);
    cout << b << endl;
    return 1;
}
