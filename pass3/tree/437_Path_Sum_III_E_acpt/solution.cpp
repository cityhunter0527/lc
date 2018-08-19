/*
 * 437. Path Sum III
 *
 * You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
 * */

#include <iostream>
using namespace std;

/** * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private: 
    // return # of path that start from root to any node that adds up to sum.
    int dfs(TreeNode* n, int sum) {
        if (!n) return 0;
        int c = 0;
        if (n->val == sum) c = 1;
        int l = dfs(n->left, sum - n->val);
        int r = dfs(n->right, sum - n->val);
        return c + l + r;
    }
public:
    int pathSum(TreeNode* root, int sum) {
        if (!root) return 0;
        int c = dfs(root, sum); // start from root to downward nodes, that's continuous to add up to sum
        int l = pathSum(root->left, sum);  // start from its left with sum
        int r = pathSum(root->right, sum); // start from its right with sum
        return c + l + r;
    }
};

int main() {
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(5);
    r->right = new TreeNode(-3);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(2);
    r->left->left->left = new TreeNode(3);
    r->left->left->right = new TreeNode(-2);
    r->left->right = new TreeNode(2);
    r->left->right->right = new TreeNode(1);
    r->right->right = new TreeNode(11);

    Solution s;
    cout << s.pathSum(r, 8) << endl;
    return 1;
}
