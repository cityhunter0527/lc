/*
 82. Remove Duplicates from Sorted List II
 Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

 For example,
 Given 1->2->3->3->4->4->5, return 1->2->5.
 Given 1->1->1->2->3, return 2->3.
*/
#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return nullptr;
        ListNode* p = head, *lastDiffNode = nullptr, *firstSameNode = p;
        while(p) {
            if (p->val != firstSameNode->val) { 
                if (firstSameNode->next == p) {
                    lastDiffNode = firstSameNode;
                    firstSameNode = p;
                } else {
                    if (lastDiffNode == nullptr) head = p;
                    else lastDiffNode->next = p;
                    firstSameNode = p;
                }
            }
            p = p->next;
        }

        if (firstSameNode->next != nullptr && lastDiffNode == nullptr) 
            return nullptr;  // <<< no diff node found and all leaving nodes are the same, return null
        if (firstSameNode->next != nullptr && lastDiffNode != nullptr) 
            lastDiffNode->next = nullptr; // <<< set diff node's next to null as all leaving nodes are the same.
        return head;
    }
};

int main() {
    ListNode* r = new ListNode(1);
    r->next = new ListNode(2);
    r->next->next = new ListNode(3);
    r->next->next->next = new ListNode(3);
    r->next->next->next->next = new ListNode(4);
    r->next->next->next->next->next = new ListNode(4);
    r->next->next->next->next->next->next = new ListNode(5);
    Solution s;
    ListNode* h = s.deleteDuplicates(r);
    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;
    
    r = new ListNode(1);
    r->next = new ListNode(1);
    r->next->next = new ListNode(1);
    r->next->next->next = new ListNode(2);
    r->next->next->next->next = new ListNode(2);
    r->next->next->next->next->next = new ListNode(4);
    h = s.deleteDuplicates(r);
    while (h) {
        cout << h->val << ", ";
        h = h->next;
    }
    cout << endl;
     
    r = new ListNode(1);
    r->next = new ListNode(1);
    r->next->next = new ListNode(1);
    r->next->next->next = new ListNode(2);
    r->next->next->next->next = new ListNode(2);
 
    h = s.deleteDuplicates(r);
    if (h != nullptr)
        cout << "FAIL" << endl;
    else 
        cout << "PASS" << endl;

    return 1;
}
