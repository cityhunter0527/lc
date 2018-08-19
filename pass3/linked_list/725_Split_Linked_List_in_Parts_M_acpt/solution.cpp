/*
 * 725. Split Linked List in Parts
 * Given a (singly) linked list with head node root, write a function to 
 * split the linked list into k consecutive linked list "parts".
 *
 * The length of each part should be as equal as possible: no two parts should 
 * have a size differing by more than 1. This may lead to some parts being null.
 *
 * The parts should be in order of occurrence in the input list, and parts occurring 
 * earlier should always have a size greater than or equal parts occurring later.
 *
 * Return a List of ListNode's representing the linked list parts that are formed.
 *
 * Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
 *
 * Example 1:
 * Input: * root = [1, 2, 3], k = 5
 * Output: [[1],[2],[3],[],[]]
 * Explanation:
 * The input and each element of the output are ListNodes, not arrays.
 * For example, the input root has root.val = 1, root.next.val = 2, \root.next.next.val = 3, and root.next.next.next = null.
 * The first element output[0] has output[0].val = 1, output[0].next = null.
 * The last element output[4] is null, but it's string representation as a ListNode is [].
 *
 * Example 2:
 * Input: 
 * root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
 * Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
 * Explanation:
 * The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.
 * Note:
 *
 * The length of root will be in the range [0, 1000].
 * Each value of a node in the input will be an integer in the range [0, 999].
 * k will be an integer in the range [1, 50].
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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<ListNode*> ans;
        int len = 0;
        ListNode* p = root;
        while (p) {
            len++;
            p = p->next;
        }
        int a = len/k, b = len%k;
        p = root;
        ListNode* nextPartHead = p, *pp = nullptr;
        while(p) {
            for (int i = 0; i < a; i++) {
                pp = p;
                p = p->next;
            }
            if (b) {
                pp = p;
                p = p->next; 
                b--;
            } 
            pp->next = nullptr;
            ans.push_back(nextPartHead);
            nextPartHead = p;
        }
        if (ans.size() < k) {
            for (int i = len%k; i < k; i++) {
                ans.push_back(nullptr);
            }
        }
        return ans;
    }
};

int main() {
    ListNode* r = new ListNode(1);
    r->next = new ListNode(2);
    r->next->next = new ListNode(3);
#if 0
    r->next->next->next = new ListNode(4);
    r->next->next->next->next = new ListNode(5);
    r->next->next->next->next->next = new ListNode(6);
    r->next->next->next->next->next->next = new ListNode(7);
    r->next->next->next->next->next->next->next = new ListNode(8);
    r->next->next->next->next->next->next->next->next = new ListNode(9);
    r->next->next->next->next->next->next->next->next->next = new ListNode(10);
#endif
    Solution s;
    vector<ListNode*> o = s.splitListToParts(r, 5);

    cout << "[";
    for (int i = 0; i < o.size(); i++) {
        cout << "[";
        ListNode* p = o[i];
        if (p == nullptr) cout << "null";
        while (p) {
            cout << p->val << ", ";
            p = p->next;
        }
        cout << "]";
    }
    cout << "]" << endl;
    return 1;
}
