/*
 * 110. Balanced Binary Tree
 *
 * Given a binary tree, determine if it is height-balanced.
 *
 * For this problem, a height-balanced binary tree is defined as a 
 * binary tree in which the depth of the two subtrees of every node never differ by more than 1.
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
    bool isb = true;
    // return hight of this node
    int dfs(TreeNode* node) {
        if (node == nullptr || !isb) return 0;
        int l = dfs(node->left);
        int r = dfs(node->right);
        if (abs(l-r) > 1) {
            isb = false;
            return 0;
        }
        else 
            return max(l, r) + 1;
    }
    bool isBalanced(TreeNode* root) {
        if (root==nullptr) return true;
        dfs(root);
        return isb;
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(1);
    r->right = new TreeNode(1);
    r->right->right = new TreeNode(1);
    Solution s;
    cout << s.isBalanced(r) << endl;
    return 1;
}
