
/*
 Given a binary tree, find the length of the longest path where 
 each node in the path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
*/

#include <iostream>
using namespace std;
/** * Definition for a binary tree node.*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int helper(TreeNode* r, int val) {
        if (r && r->val == val)
            return 1 + max(helper(r->left, val), helper(r->right, val));
        return 0;
    }
    int longestUnivaluePath(TreeNode* root) {
        if (!root) return 0;
        return max(max(longestUnivaluePath(root->left), longestUnivaluePath(root->right)), 
                   helper(root->left, root->val) + helper(root->right, root->val));
    }
};

int main() {
    return 1;
}
