/*
 * 124. Binary Tree Maximum Path Sum  
 *
 * Given a binary tree, find the maximum path sum.
 *
 * For this problem, a path is defined as any sequence of nodes from some 
 * starting node to any node in the tree along the parent-child connections. 
 * The path does not need to go through the root.
 *
 * For example:
 * Given the below binary tree,
 *
 *        1
 *       / \
 *      2   3
 * Return 6.
 *
 *        1
 *       / \
 *      2   3
 *     / \
 *    6   9
 * Return 17 (6+2+9)
 * * */
#include <iostream>
#include <climits>
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
    int maxSum = INT_MIN;
    // postOrder traversal;
    // A path from start to end, goes up on the tree for 0 or more steps, 
    // then goes down for 0 or more steps. Once it goes down, it can't go up. 
    // Each path has a highest node, which is also the lowest common ancestor 
    // of all other nodes on the path.
    // 
    // A recursive method maxPathDown(TreeNode node) 
    //   (1) Computes the maximum path sum with highest node is the input node, 
    //       update maximum if necessary 
    //   (2) Returns the maximum sum of the path that can be extended to input node's parent.
    //   Complexity: O(N)
    int maxPathSum(TreeNode* root) {
        maxPathSumDown(root);
        return maxSum;
    }
    int maxPathSumDown(TreeNode* root) {
        if (root == NULL) return 0;
        int leftMax = max(0, maxPathSumDown(root->left));
        int rightMax = max(0, maxPathSumDown(root->right));
        maxSum = max(maxSum, root->val + leftMax + rightMax);
        return max(leftMax, rightMax) + root->val;
    }
};

int main () {
/*
 *        1
 *       / \
 *      2   3
 *     / \
 *    6   9
 **/
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(6);
    r->left->right = new TreeNode(9);
    Solution s;
    int v = s.maxPathSum(r);
    cout << v << endl;
    return 1;
}

