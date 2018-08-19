/*
 * 25. Reverse Nodes in k-Group
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
 *
 * k is a positive integer and is less than or equal to the length of the linked list. 
 * If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
 *
 * You may not alter the values in the nodes, only nodes itself may be changed.
 *
 * Only constant memory is allowed.
 *
 * For example,
 * Given this linked list: 1->2->3->4->5
 *
 * For k = 2, you should return: 2->1->4->3->5
 * For k = 3, you should return: 3->2->1->4->5
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
private: 
    ListNode* reverse(ListNode* head) {
        ListNode* dummyNode = new ListNode(0);
        ListNode* tmp;
        while (head) {
            tmp = head->next;
            head->next = dummyNode->next;
            dummyNode->next = head;
            head = tmp;
        }
        return dummyNode->next;
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) return nullptr;
        ListNode* newHead = nullptr, *curKGroupHead = nullptr, *prevKGroupTail = nullptr;
        ListNode* tmp = nullptr, *savedTail = head; // << savedTail is for prevKGroupTail when cnt reaches k
        int cnt = 0;
        while (head) {
            cnt++;
            // do reverse
            tmp = head->next;
            head->next = curKGroupHead;
            curKGroupHead = head;
            head = tmp;
            if (cnt == k){
                // we've got a K group, now neal the previous K-1 group to this group.
                // and saveTail for next round
                cnt = 0;   
                if (prevKGroupTail) {
                    prevKGroupTail->next = curKGroupHead;
                    curKGroupHead = nullptr;
                } else {
                    newHead = curKGroupHead;
                    curKGroupHead = nullptr;
                }
                prevKGroupTail = savedTail;
                savedTail = head; // <<< Update savedTail
            }
        }
        // need to reverse back the last part when k is not multiple of list length
        if (cnt < k) {
            if (prevKGroupTail) 
                prevKGroupTail->next = reverse(curKGroupHead);   
            else 
                newHead = reverse(curKGroupHead); // <<< k is larger then list length, need to reverse back;
        }
        return newHead;
    }
};

int main() {
    ListNode* l = new ListNode(1);
    l->next = new ListNode(2);
    l->next->next = new ListNode(3);
    
    Solution s;
    ListNode* h = s.reverseKGroup(l, 4);
    while (h) {
        cout << h->val << ",";
        h = h->next;
    }
    cout << endl;
    return 1;
}
