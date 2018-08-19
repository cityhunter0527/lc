/* 
 * 98. Validate Binary Search Tree
 *
 * Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:
    2
   / \
  1   3
Binary tree [2,1,3], return true.
Example 2:
    1
   / \
  2   3
Binary tree [1,2,3], return false.
 * */


#include <iostream>
#include <assert.h>
using namespace std;

/** *  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    // 
    // bottom up
    // for every node:
    //     1. if it is left child, it's val < parent's val and its "right most child" < parent's value
    //     2. if it is right child, it's val > parent's val and its "left most child" > parent's value
    //
    TreeNode* getLRMostNode(TreeNode* n, bool l) {
        if (l) {
            while (n->left) n = n->left;
        } else {
            while (n->right) n = n->right;
        }
        return n;
    }
    bool helper(TreeNode* n, TreeNode* parent) {
        if (!n) return true;
        if (parent) {
            if (n == parent->left) {
                if (n->val >= parent->val || (n->right && getLRMostNode(n, false)->val >= parent->val)) 
                    return false;
            } else { 
                if (n->val <= parent->val || (n->left && getLRMostNode(n, true)->val <= parent->val))
                    return false;
            }
        } 
        return helper(n->left, n) && helper(n->right, n);
    }
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        return helper(root, nullptr);
    }
};

//
//
// 
int main() {
    TreeNode* r = new TreeNode(3);   
    r->left = new TreeNode(2);
    r->right = new TreeNode(5);

    Solution s;
    cout << s.isValidBST(r) << endl;


    return 1;
}
