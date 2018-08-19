/*
 * 156. Binary Tree Upside Down
 * Given a binary tree where all the right nodes are either leaf nodes with a sibling 
 * (a left node that shares the same parent node) or empty, flip it upside down and 
 * turn it into a tree where the original right nodes turned into left leaf nodes. 
 * Return the new root.
 *
 * For example:
 * Given a binary tree {1,2,3,4,5},
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 *return the root of the binary tree [4,5,2,#,#,3,1].
 *     4
 *    / \
 *   5   2
 *      / \
 *     3   1  
 * */


#include <iostream>
using namespace std;

/*** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // iterative
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        TreeNode* cur = root, *nextRoot = nullptr, *prevRoot = nullptr, *lastRightLeaf= nullptr;

        while (cur) {
            nextRoot = cur->left;
            cur->left = lastRightLeaf;
            lastRightLeaf = cur->right;
            cur->right = prevRoot;
            prevRoot = cur;
            cur = nextRoot;
        }

        return cur;
    }

    // recursive
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (root == nullptr || root->left == nullptr) 
            return root;
        // 1. parent's left to be new-parent.
        // 2. parent to be right child of new-parent
        // 3. parent's right child to be left child of new-parent
        TreeNode* newRoot = upsideDownBinaryTree(root->left);
        root->left->right = root;
        root->left->left = root->right;
        root->right = nullptr;
        root->left = nullptr;
        retrn newRoot;
    }
};
