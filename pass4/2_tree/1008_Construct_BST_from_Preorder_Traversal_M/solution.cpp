/*
 * 1008 Construct Binary Search Tree from Preorder Traversal
 * Return the root node of a binary search tree that matches the given preorder traversal.
 *
 *  Example 1:
 *          8
 *         / \
 *        5   10
 *       / \    \
 *      1   7   12  
 *
 *  Input: [8,5,1,7,10,12]
 *  Output: [8,5,10,1,7,null,12]
 *
 *   Note: 
 *
 *   1 <= preorder.length <= 100
 *   The values of preorder are distinct.
 * */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
                           
    }
};
