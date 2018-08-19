/*
 * 98. Validate Binary Search Tree
 *
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 * Example 1:
 *     2
 *    / \
 *   1   3
 *  Binary tree [2,1,3], return true.
 *  
 *  Example 2:
 *     1
 *    / \
 *   2   3
 *  Binary tree [1,2,3], return false.
 * */

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
};

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, (long)INT_MIN-1, (long)INT_MAX+1);       
    }

private:
    // pre-order traversal. 
    bool isValidBST(TreeNode* r, long lowerVal, long upperVal) {
        if (r==nullptr) 
            return true;
        return r->val > lowerVal && r->val < upperVal &&
                isValidBST(r->left, lowerVal, r->val) &&
                isValidBST(r->right, r->val, upperVal);
    }
};

int main () {
    //[2147483647]
    return 1;
}
