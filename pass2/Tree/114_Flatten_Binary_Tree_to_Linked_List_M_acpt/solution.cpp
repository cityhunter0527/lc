/*
  114. Flatten Binary Tree to Linked List

 Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
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
    // for each node (postOrder, bottom-up):
    // 1. flatten its left child
    // 2. flatten its right child
    //
    TreeNode* dfs(TreeNode* node) {
        if (node == nullptr) return node;
        TreeNode* lrm = dfs(node->left);
        TreeNode* rrm = dfs(node->right);
        
        if (lrm == nullptr) 
            return rrm?rrm:node;

        TreeNode* tmp = node->right;
        node->right = node->left;
        lrm->right = tmp;
        node->left = nullptr;

        return rrm?rrm:lrm;
    } 
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        dfs(root);
    }
};

int main() {
#if 0
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(5);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(4);
    r->right->right = new TreeNode(6);
#endif
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->left->left = new TreeNode(3);
    Solution s;
    s.flatten(r);
    return 1;
}
