/*
 * 160. Intersection of Two Linked Lists
 *
 * Write a program to find the node at which the intersection of two singly linked lists begins.
For example, the following two linked lists:

A:          a1 -> a2
                    -> 
                       c1 -> c2 -> c3
                    ->       
B:    b1 -> b2 -> b3
begin to intersect at node c1.
Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
 * */

#include <iostream>
using namespace std;

/** * Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB = 0;       
        ListNode* p = headA;
        while(p) {
            lenA++; 
            p = p->next;
        }
        p = headB;
        while (p) {
            lenB++;
            p = p->next;
        } 
        // now proceed the longer list with steps equals to abs(lenA-lenB)
        ListNode* q;
        if (lenA > lenB) {
            p = headA;
            while (p && lenA > lenB) {
                lenA--;
                p = p->next;
            }
            q = headB;
        } else {
            p  = headB;
            while (p && lenB > lenA) {
                lenB--;
                p = p->next;
            }
            q = headA;
        }
        // now the intersect node must occur on the same step
        while (p != q) {
            p = p->next;
            q = q->next;
        }
        return p;
    }
};
int main() {
    ListNode* l = new ListNode(1);
    l->next = new ListNode(2);
    l->next->next = new ListNode(3);
    l->next->next->next = new ListNode(4);
    l->next->next->next->next = new ListNode(5);
    ListNode* l2 = new ListNode(11);
    l2->next = new ListNode(12);
    l2->next->next = new ListNode(13);
    l2->next->next->next = l->next->next;

    Solution s;
    ListNode* n = s.getIntersectionNode(l, l2);
    cout << n->val << endl;
    
    return 1;
}
