/** 
 * 109. Convert Sorted List to Binary Search Tree
 *
 * Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
 **/

#include <iostream>
using namespace std;

/** Definition for singly-linked list. **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return new TreeNode(head->val);
        ListNode* l = nullptr, *r = nullptr;
        int mid = frontBackSplitMid(head, l, r);
        TreeNode* n = new TreeNode(mid);
        n->left = sortedListToBST(l);
        n->right = sortedListToBST(r);
        return n;
    }
private:
    // split left and right and return mid node's value; 
    // mid node should not be in either l or r;
    int frontBackSplitMid(ListNode* head, ListNode*& l, ListNode*& r) {
        ListNode* slow = head, *pslow = nullptr;
        ListNode* fast = head->next;
        ListNode* savedHead = head;
        while (fast && fast->next) {
            pslow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        int mid = slow->val;
        if (pslow) {
            pslow->next = nullptr; // remove mid node from l
            l = savedHead;
        } else {
            l = nullptr;
        }
        r = fast;
        return mid;
    }
};

int main () {
    ListNode* r = new ListNode(1);
    r->next = new ListNode(2);
    r->next->next = new ListNode(3);
    r->next->next->next = new ListNode(4);
    r->next->next->next->next = new ListNode(5);
    
    Solution s;
    TreeNode* root = s.sortedListToBST(r);

    return 1;
}
