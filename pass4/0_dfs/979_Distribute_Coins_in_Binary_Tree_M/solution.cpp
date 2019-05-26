/*  
 *  979. Distribute Coins in Binary Tree
 * 
Given the root of a binary tree with N nodes, each node in the tree has node.val coins, 
and there are N coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to another.  
(The move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.

Example 1:
     3
    / \
   0   0

Input: [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.


Example 2:
     0
    / \
   3   0

Input: [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root [taking two moves].  Then, we move one coin from the root of the tree to the right child.


Example 3:
      1
     / \
    0   2 
Input: [1,0,2]
Output: 2


Example 4:
      1
    /   \
   0     0
    \
     3
Input: [1,0,0,null,3]
Output: 4

Note:
1<= N <= 100
0 <= node.val <= N
 * */

#include <iostream>
#include <cassert>

/** * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // return number of coins needed for this sub-tree
    int dfs(TreeNode* x) {
        if (x == nullptr) { 
            return 0;
        }
        return dfs(x->left) + dfs(x->right) + x->val-1;
    }

    int distributeCoins(TreeNode* root) {
        if (root == nullptr) { 
            return 0;
        }
        // 
        // 1. from this root node, give dfs(root->left) nodes to left, 
        //    then give dfs(root->right) nodes to right, so each sub-tree have enough nodes to do distribution.
        // 2. plus distruteCoins of left sub-tree and
        // 3. plus distruteCoins of right sub-tree
        // 
        return abs(dfs(root->left)) + abs(dfs(root->right)) + distributeCoins(root->left) + distributeCoins(root->right); 
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(0);
    root->right = new TreeNode(0);
    Solution s;
    assert(s.distributeCoins(root) == 2);

    //        5
    //       /
    //      0
    //     /
    //    0
    //   / \
    //  0   0
    root = new TreeNode(5);
    root->left = new TreeNode(0);
    root->left->left = new TreeNode(0);
    root->left->left->left = new TreeNode(0);
    root->left->left->right = new TreeNode(0);
    assert(s.distributeCoins(root) == 9);

    return 1;
}
