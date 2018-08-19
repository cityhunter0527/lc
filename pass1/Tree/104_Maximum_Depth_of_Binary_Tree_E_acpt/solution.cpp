/*
 * 104. Maximum Depth of Binary Tree
 *
 * Given a binary tree, find its maximum depth.
 *
 * The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 * */

#include <iostream>
using namespace std;
/** *  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        return 1 + max(l,r);
    }
};

//
//             1
//           /   \
//          2     3
//           \   / \
//            4 5   6
//               \
//                7
// 
int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->right = new TreeNode(4);
    r->right->left = new TreeNode(5);
    r->right->right = new TreeNode(6);
    r->right->left->right = new TreeNode(7);
    Solution s;
    int v = s.maxDepth(r);
    cout << v << endl;
    return 1;
}
