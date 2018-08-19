/*
 * 437. Path Sum III
 *
 * You are given a binary tree in which each node contains an integer value.
 * Find the number of paths that sum to a given value.
 * The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
 * The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.
 *
 * Example:
 *
 * root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
 *
 *       10
 *      /  \
 *     5   -3
 *    / \    \
 *   3   2   11
 *  / \   \
 * 3  -2   1
 *
 * Return 3. The paths that sum to 8 are:
 *
 * 1.  5 -> 3
 * 2.  5 -> 2 -> 1
 * 3. -3 -> 11
 * */
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};
    
class Solution {
public:
    // 1. get the num of path that's "continously connected" from this node to some node downward;
    int dfs(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        int l = dfs(root->left, sum - root->val);
        int r = dfs(root->right, sum - root->val);
        int c = 0;
        if (sum == root->val) c = 1; // <<< can't stop here, as we need to keep search downward until 
                                     // <<< leaf node as downward nodes could adds up to 0 which 
                                     // <<< makes another acceptable path.
        return c + l + r;
    }

    // for every node:
    // 1. get the num of path that's "continously connected" from this node to some node downward;
    // 2. get the path sum of it's left child.
    // 3. get the path sum of it's right child.
    // 4, return sum of number returned from (1,2,3)
    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        // get the number of path starting from "root", which must be continous.
        int n = dfs(root, sum);
        // get the number of path of left child;
        int sumL = pathSum(root->left, sum);
        // get the number of path of right child;
        int sumR = pathSum(root->right, sum);
        return n + sumL + sumR;
    }
};

int main() {
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(5);
    r->right = new TreeNode(-3);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(2);
    r->right->right = new TreeNode(11);
    r->left->left->left = new TreeNode(3);
    r->left->left->right = new TreeNode(-2);
    r->left->right->right = new TreeNode(1);

    Solution s;
    cout << s.pathSum(r, 8) << endl;

    return 1;
}
