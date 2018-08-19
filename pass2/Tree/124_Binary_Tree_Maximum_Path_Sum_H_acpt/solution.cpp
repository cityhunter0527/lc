/*
 * 124. Binary Tree Maximum Path Sum
 *
 * Given a binary tree, find the maximum path sum.
 *
 * For this problem, a path is defined as any sequence of nodes 
 * from some starting node to any node in the tree along the parent-child 
 * connections. The path must contain at least one node and does not need to go through the root.
 *
 * For example:
 * Given the below binary tree,
 *        1
 *       / \
 *      2   3
 * Return 6.
 * */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;
/** *  Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxSum = INT_MIN;
    // 
    // For any path, it must have a higest node (once go down, never go up, 
    // because every node has and only has one parent).
    //
    // for each node in tree (bottom up, postOrder Traversal):
    // * Compute it's maxPathSum with this node as highest node.
    // * Recusively compare with curMaxSum and update it when necessary.
    // * it returns the maxSum with down path so that it can give hint to 
    //   its parent to do recusive calculation.
    //
    int maxPathSum(TreeNode* root) {
        maxPathDown(root);
        return maxSum;
    }
    // This function do two things:
    // * return max sum path *down* (so that its parent could use this information recursively from bottom to up)
    // * calculate maxPathSum with this node as highest and update maxSum when necessary.
    // * repeat this function for every node in the tree with postOrder Traversal(bottom up).
    int maxPathDown(TreeNode* node) {
        if (node == nullptr) return 0;
        int lMax = max(0, maxPathDown(node->left));
        int rMax = max(0, maxPathDown(node->right));
        // Update maxSum when necessary
        maxSum = max(maxSum, node->val + lMax + rMax);
        return max(lMax, rMax) + node->val;  // return down max path sum 
    }
};

int main () {
    //        -10
    //      /    \
    //     3       14
    //   /   \    /   \
    //  8     2  -1    -2
#if 0
    TreeNode* r = new TreeNode(-10);
    r->left = new TreeNode(3);
    r->right = new TreeNode(14);
    r->left->left = new TreeNode(8);
    r->left->right = new TreeNode(2);
    r->right->left = new TreeNode(-1);
    r->right->right = new TreeNode(-2);
#endif
    TreeNode* r = new TreeNode(-2);
    r->left = new TreeNode(1);
    Solution s;
    cout << s.maxPathSum(r) << endl;
    return 1;
}
