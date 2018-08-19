/**
 * Recover Binary Search Tree
 *
 * Two elements of a binary search tree (BST) are swapped by mistake.
 *
 * Recover the tree without changing its structure.
 *
 * Note:
 * A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
 * */
#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    // in-Order Traversal 
    void recoverTree(TreeNode *root) {
        stack<TreeNode *> s;
        TreeNode* cur = root;
        TreeNode* first = NULL; 
        TreeNode* second = NULL;
        TreeNode* prev = NULL;
        while (!s.empty() || cur) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                cur = s.top();
                s.pop();
                if (prev != NULL && cur->val < prev->val) {
                    // incorrect smaller node is always found as prev node
                    if (first == NULL) first = prev;
                    // incorrect larger node is always found as curr node
                    second = cur;
                } 
                prev = cur;
                cur = cur->right;
            }
        }
        int v = first->val;
        first->val = second->val;
        second->val = v;
        return;
    }
};

int main() {
    return 1;
}
