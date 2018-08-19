/*
 * 222. Count Complete Tree Nodes
 * Given a complete binary tree, count the number of nodes.
 *
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the last, is completely filled, 
 * and all nodes in the last level are as far left as possible. 
 *
 * It can have between 1 and 2h nodes inclusive at the last level h.
 *
 * */

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
/*** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // Do binary search on a binary tree
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int hl = 0, hr = 0;
        TreeNode* lr = root, *rr = root;
        while (lr) {hl++; lr = lr->left;}
        while (rr) {hr++; rr = rr->right;}
        if (hl == hr) return pow(2, hl) - 1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

int main () {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(1);
    root->left->left->left = new TreeNode(1);
    root->left->left->right = new TreeNode(1);
    root->left->right->left = new TreeNode(1);
    root->left->right->right = new TreeNode(1);

    root->right->left =  new TreeNode(1);
    root->right->right =  new TreeNode(1);

    root->right->left->left =  new TreeNode(1);

    Solution s;
    int v = s.countNodes(root);
    cout<<v<<endl;
    return 1;
}
