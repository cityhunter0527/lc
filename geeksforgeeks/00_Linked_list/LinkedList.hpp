#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <iostream>
#include <vector>
using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr){}
};

class Solution {
private:
    int getListLen(ListNode* x) {
        int len = 0;
        while (x) {
            x = x->next;
            len++;
        }
        return len;
    }

    ListNode* reverse(ListNode* x) {
        ListNode dummy(1), *p = nullptr;
        while (x) {
            p = x->next;
            x->next = dummy.next;
            dummy.next = x;
            x = p;
        }
        return dummy.next;
    }
    
    void frontBackSplit(ListNode* head, ListNode*& a, ListNode*& b);
    ListNode* sortedMerge(ListNode* l1, ListNode* l2);
    void insertSorted(ListNode* dummy, ListNode* x);
    ListNode *detectIntersect(ListNode *l1, int len1, ListNode* l2, int len2);
    int dist(ListNode *start, ListNode* end);
public:
    // 23. Merge k Sorted Lists
    ListNode* mergeKLists(vector<ListNode*>& lists);
    // 142. Linked List Cycle II
    ListNode *detectCycle(ListNode *head);
    // 147. Insertion Sort List
    ListNode* insertionSortList(ListNode* head);
    // 148. Sort List
    ListNode* sortList(ListNode* head);
    // 328. Odd Even Linked List
    ListNode* oddEvenList(ListNode* head);
    // 445. Add Two Numbers II
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
    ListNode* addTwoNumbersOpt1(ListNode* l1, ListNode* l2);
    // 725. Split Linked List in Parts
    vector<ListNode*> splitListToParts(ListNode* root, int k);
    // MS Interview: Detect Intersect node
    // 1. No Cycle; 2. With Cycle;
    ListNode *detectIntersect(ListNode *l1, ListNode* l2);
};
#endif
