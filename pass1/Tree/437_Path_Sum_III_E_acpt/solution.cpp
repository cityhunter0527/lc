/*
 * 437. Path Sum III
 * You are given a binary tree in which each node contains an integer value.
 * Find the number of paths that sum to a given value.
 * The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
 * The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.
 * Example:
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
    TreeNode* left, *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};
class Solution {
public:
    // [1,null,2,null,3,null,4,null,5]
    //        1
    //         \
    //          2
    //           \
    //            3
    //             \
    //              4
    //               \
    //                5
    int helper(TreeNode* root, int sum) {
        // for every starting node, seek from this node down to leaf for every combination of sum;
        if (root == nullptr) return 0;
        int l = helper(root->left, sum-root->val);
        int r = helper(root->right, sum-root->val);
        return (root->val == sum? 1:0) + l + r; // should not stop when we found a match, but keep downwarding.

    }
    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        int v = helper(root, sum);
        return v + pathSum(root->left, sum) + pathSum(root->right, sum); // downward starting with every node with Sum;
    }
};

int main() {
#if 0
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(5);
    r->right = new TreeNode(-3);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(2);
    r->left->left->left = new TreeNode(3);
    r->left->left->right = new TreeNode(-2);
    r->left->right->right = new TreeNode(1);
    r->right->right = new TreeNode(11);
    Solution s;
    int v = s.pathSum(r, 8);
    assert (v==3);
    cout << v << endl;
#endif
    TreeNode* r = new TreeNode(1);
    r->right = new TreeNode(2);
    r->right->right = new TreeNode(3);
    r->right->right->right = new TreeNode(4);
    r->right->right->right->right = new TreeNode(5);

    Solution s;
    int v = s.pathSum(r, 3);
    cout << v << endl;
    return 1;
}
