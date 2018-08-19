/*
 * 250. Count Univalue Subtrees
 *
 * Given a binary tree, count the number of uni-value subtrees.
 *
 * A Uni-value subtree means all nodes of the subtree have the same value.
 *
 * For example:
 * Given binary tree,
 *               5
 *              / \
 *             1   5
 *            / \   \
 *           5   5   5
 * return 4.
 * */

#include <iostream>
using namespace std;
/**  * Definition for a binary tree node.**/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int numUniTrees = 0;
    int countUnivalSubtrees(TreeNode* root) {
        helper(root);
        return numUniTrees;
    }

    // bottom-up manner
    bool helper(TreeNode* root) {
        if (root == nullptr) return true;
        if (root->left == nullptr && root->right == nullptr) {
            // leaf node is uni-val subTree
            numUniTrees++;
            return true;
        }
        bool l = helper(root->left);
        bool r = helper(root->right);
        if (l && r && 
            ((root->left == nullptr && root->val == root->right->val) || // left child is null
             (root->right == nullptr && root->val == root->left->val) || // right child is null
             (root->right && root->left && root->left->val == root->val && root->val == root->right->val))) { // neither left nor right is null
                numUniTrees++;
                return true;
        } else 
            return false;
    }
};

int main () {
    // [1,null,2]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
#if 0
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(5);
#endif
    Solution s;
    int v = s.countUnivalSubtrees(root);
    cout << v << endl;
    return 1;
}
