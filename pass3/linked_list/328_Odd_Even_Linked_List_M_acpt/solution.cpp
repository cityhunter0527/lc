/* * 328. Odd Even Linked List 
 * Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
 *
 * You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.
 *
 * Example:
 * Given 1->2->3->4->5->NULL,
 * return 1->3->5->2->4->NULL.
 *
 * Note:
 * The relative order inside both the even and odd groups should remain as it was in the input. 
 * The first node is considered odd, the second node even and so on ...
 * * */


#include <iostream>
using namespace std;

/*** Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return nullptr;

        ListNode* lastEven = head->next, *lastOdd = head;
        
        while (lastEven) {
            if (lastEven->next) {
                // found odd node 
                ListNode* p = lastEven->next->next;
                ListNode* firstEven = lastOdd->next;
                lastOdd->next = lastEven->next;
                lastOdd->next->next = firstEven;
                lastEven->next = p;

                lastOdd = lastOdd->next;
                lastEven = lastEven->next;
            } else
                break; // we are done;
            
        }

        return head;
    }
};

int main() {
    ListNode* h = new ListNode(1);
    h->next = new ListNode(2);
    h->next->next = new ListNode(3);
    h->next->next->next = new ListNode(4);
    h->next->next->next->next = new ListNode(5);
    Solution s;
    h = s.oddEvenList(h);

    while (h) {
        cout << h->val << "->";
        h = h->next;
    }
    cout << endl;
    return 1;
}
