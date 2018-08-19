/*
 * 445. Add Two Numbers II
 * You are given two non-empty linked lists representing two non-negative integers. 
 * The most significant digit comes first and each of their nodes contain a single digit. 
 * Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Follow up:
 * What if you cannot modify the input lists? In other words, reversing the lists is not allowed.
 *
 * Example:
 *
 * Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 8 -> 0 -> 7
 *
 * */
#include <iostream>
#include <climits>
using namespace std;
/** *  * Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private: 
    ListNode* reverse(ListNode* l) {
        ListNode* head = nullptr, *tmp = nullptr;
        while (l) {
            tmp = l->next;
            l->next = head;
            head = l;
            l = tmp;
        }
        return head;
    }
public:
    // construct new linked list rl1 w/ reversed sequence
    // construct new listed list rl2 w/ reversed sequence
    // dim = 0;
    //
    // re-using exiting list rl1:
    // traversal each node in rl1&rl2, for each node n1, n2 in rl1 and rl2 respectively:
    // 1. constrct this node with value (n1 + n2 + dim)/10
    // 2. if n1 + n2 + dim > 10, set dim as 1, otherwise set dim as 0;
    //
    // return reversed of rl1;
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // reverse l1 and l2;
        l1 = reverse(l1);
        l2 = reverse(l2);
        ListNode* savedHead = l1, *pl1 = nullptr;
        unsigned char dim = 0, sum = 0;
        while (l1 && l2) {
            sum = dim + l1->val + l2->val;
            l1->val = sum%10;
            dim = sum/10;
            pl1 = l1;
            l1 = l1->next;
            l2 = l2->next;
        }
        
        if (l1 == nullptr) pl1->next = l2;
        
        l1 = pl1->next;
        
        // keep adding dim to rest of the list
        while (l1) {
            l1->val += dim;
            dim = l1->val/10;
            l1->val %= 10;
            pl1 = l1;
            l1 = l1->next;
        }
        if (dim) pl1->next = new ListNode(1);

        return reverse(savedHead);
    }
};
int main() {
    ListNode* l1 = new ListNode(3);
    l1->next = new ListNode(9);
    l1->next->next = new ListNode(9);
    l1->next->next->next = new ListNode(9);
    l1->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next->next->next->next = new ListNode(9);
    l1->next->next->next->next->next->next->next->next->next = new ListNode(9);
    
    ListNode* l2 = new ListNode(7);

    Solution s;
    ListNode* p = s.addTwoNumbers(l1, l2);

    while (p) {
        cout << p->val;
        p = p->next;
    }
    cout << endl;
    return 1;
}
