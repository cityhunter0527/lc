/*
 * 114. Flatten Binary Tree to Linked List 
 * Given a binary tree, flatten it to a linked list in-place.
 *
 * For example,
 * Given
 *
 *          1
 *         / \
 *        2   5
 *       / \   \
 *      3   4   6
 *
 * The flattened tree should look like:
 *          1
 *           \
 *            2
 *             \
 *              3
 *               \
 *                4
 *                 \
 *                  5
 *                   \
 *                    6
 * */
#include <iostream>
#include <stack>
using namespace std;
/** Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void flatten(TreeNode* root) { 
        if (root == nullptr) return;
        stack<TreeNode*> s;
        TreeNode* prev = nullptr;
        s.push(root);
        while (!s.empty()) {
            TreeNode* p = s.top();
            s.pop();
            // visit p
            if (prev) {
                prev->right = p;
                prev->left = nullptr;
                prev = p;
            } else {
                prev = p;
            }
            if (p->right)
                s.push(p->right);
            if (p->left)
                s.push(p->left);
        }
    }
};

int main () {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);

    Solution s;
    s.flatten(root);

    return 1;
}
