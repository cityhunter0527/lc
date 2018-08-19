/*
 * 226. Invert Binary Tree
 *
 * Invert a binary tree.
 *
 *      4
 *    /   \
 *   2     7
 *  / \   / \
 * 1   3 6   9
 * to
 *      4
 *    /   \
 *   7     2
 *  / \   / \
 * 9   6 3   1
 * */
#include <iostream>
#include <vector>
using namespace std;
/** *  * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    // recursive
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* tmp = root->right;
        root->right = invertTree(root->left);
        root->left = invertTree(tmp);
        return root;
    }
};

int main () {
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(2);
    r->right = new TreeNode(7);
    r->left->left = new TreeNode(1);
    r->left->right = new TreeNode(3);
    r->right->left = new TreeNode(6);
    r->right->right = new TreeNode(9);
    Solution s;
    TreeNode* nr =  s.invertTree(r);
    return 1;
}
