/** 
 * 148. Sort List
 *
 * Sort a linked list in O(n log n) time using constant space complexity. 
 * **/

#include <iostream>
#include <assert.h>
using namespace std;

/** Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    //MergeSort(headRef)
    //1) If head is NULL or there is only one element in the Linked List then return.
    //2) Else divide the linked list into two halves.  
    //       FrontBackSplit(head, &a, &b); /* a and b are two halves */
    //3) Sort the two halves a and b.
    //       MergeSort(a);
    //       MergeSort(b);
    //4) Merge the sorted a and b (using SortedMerge() discussed here) 
    //   and update the head pointer using headRef.
    //       *headRef = SortedMerge(a, b);
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* a = nullptr, *b = nullptr;
        FrontBackSplit(head, a, b);
        a = sortList(a);
        b = sortList(b);
        return SortedMerge(a, b);
    }
private:
    // slow, fast pointer
    void FrontBackSplit(ListNode* head, ListNode*& a, ListNode*& b) {
        assert(head && head->next);
        ListNode* slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        slow->next = nullptr;    
        slow = head;
        a = slow;
        b = fast;
        return;
    }
    ListNode* SortedMerge(ListNode* l1, ListNode* l2) {
        assert(l1 && l2);
        ListNode* dummyNode = new ListNode(0), **p = &dummyNode->next;
        while (l1 && l2) {
            if (l1->val < l2->val) { 
                *p = l1; 
                l1 = l1->next;
            } else {
                *p = l2;
                l2 = l2->next;   
            }
            (*p)->next = nullptr;
            p = &(*p)->next;
        }
        if (l1 == nullptr) *p = l2;
        else *p = l1;
        return dummyNode->next;
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
    ListNode* h = s.sortList(l1);
    while (h) {
        cout << h->val << endl;
        h = h->next;
    }
    cout << endl;
    return 1;
}
