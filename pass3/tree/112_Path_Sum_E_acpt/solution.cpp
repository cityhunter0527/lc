/* 
   112. Path Sum

 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
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
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (root->val == sum && !root->left && !root->right) return true;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

int main () {
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(4);
    r->right = new TreeNode(8);
    r->left->left = new TreeNode(11);
    r->left->left->left = new TreeNode(7);
    r->left->left->right = new TreeNode(2);

    r->right->left = new TreeNode(13);
    r->right->right = new TreeNode(4);
    r->right->right->right = new TreeNode(1);

    Solution s;
    cout << s.hasPathSum(r, 22) << endl;
    cout << s.hasPathSum(r, 23) << endl;
    cout << s.hasPathSum(r, 26) << endl;
    cout << s.hasPathSum(r, 27) << endl;
    cout << s.hasPathSum(r, 18) << endl;
    cout << s.hasPathSum(r, 9) << endl;
    cout << s.hasPathSum(r, 19) << endl;
    return 1;
}
