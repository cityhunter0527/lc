/*
 * Find the sum of all left leaves in a given binary tree.
 *
 * Example:
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *        /
 *       1
 *
 * There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
 * */
#include <iostream>
using namespace std;
/** Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // in- order traversal
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) return 0;
        int sum = 0;
        // if root's left child is a leaf, add it;
        if (root->left && !root->left->left && !root->left->right) {
            sum += root->left->val;
        } 
        // keep visiting root's left child
        sum += sumOfLeftLeaves(root->left);
        // keep visiting root's right child
        sum += sumOfLeftLeaves(root->right);
        return sum;
    }
};

int main() {
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(9);
    r->right = new TreeNode(20);
    r->right->left = new TreeNode(15);
    r->right->right = new TreeNode(7);
    r->right->right->left = new TreeNode(1);

    Solution s;
    cout << s.sumOfLeftLeaves(r) << endl;
    return 1;
}
