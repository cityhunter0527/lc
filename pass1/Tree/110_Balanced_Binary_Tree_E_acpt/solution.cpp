/*
 * 110. Balanced Binary Tree
 * Given a binary tree, determine if it is height-balanced.
 *
 * For this problem, a height-balanced binary tree is defined as a binary tree 
 * in which the depth of the two subtrees of every node never differ by more than 1.
 * */

#include <iostream>
#include <climits>
using namespace std;

/*** Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // bottom up
    // For each node:
    // - get left child's height
    //   if -1, return -1;
    // - get right child's height
    //   if -1, return -1;
    // - if this node's subtree is balanced, return height;
    //   else return -1;
    int depth(TreeNode* root) {
        if (root == nullptr) return 0;
        int l = depth(root->left);
        if (l == -1) return -1;
        int r = depth(root->right);
        if (r == -1) return -1;
        if (abs(l-r)>1) return -1;
        return max(l,r) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return depth(root) != -1;
    }
};
//
//           1
//          / \
//         2   3
//        / \   \
//       4   5   7
//            \
//             6
// 
int main () {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->left->right = new TreeNode(5);
    r->left->right->right = new TreeNode(6);
    r->right->right = new TreeNode(7);

    Solution s;
    bool b = s.isBalanced(r);
    cout << b << endl;
    return 1;
}
