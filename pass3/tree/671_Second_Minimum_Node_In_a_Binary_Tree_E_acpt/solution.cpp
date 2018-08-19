/*
Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input: 
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input: 
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
*/

#include <iostream>
using namespace std;
/** * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    // find minal value of the input subTree that is not equal to rootVal
    // if there is non such value, return -1;
    int dfs(TreeNode* n, int rootVal) {
        if (!n) return -1;
        if (n->val != rootVal) return n->val; // we've got a match since all nodes in n's subTree will not be larger than n
        int lmin = dfs(n->left, rootVal);
        int rmin = dfs(n->right, rootVal);
        if (lmin == -1) return rmin;
        if (rmin == -1) return lmin;
        return min(lmin, rmin);
    }
public:
    int findSecondMinimumValue(TreeNode* root) {
        return dfs(root, root->val);
    }
};

int main() {
    TreeNode* r = new TreeNode(2);
    r->left = new TreeNode(2);
    r->right = new TreeNode(5);
    r->right->left = new TreeNode(5);
    r->right->right = new TreeNode(7);
    Solution s;
    cout << s.findSecondMinimumValue(r) << endl;
    return 1;
}
