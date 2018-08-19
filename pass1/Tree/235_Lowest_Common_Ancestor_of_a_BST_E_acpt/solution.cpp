/*
 *  235. Lowest Common Ancestor of a Binary Search Tree
 *  Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
 *  According to the definition of LCA on Wikipedia: "The lowest common ancestor is defined between two 
 *  nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node 
 *  to be a descendant of itself)."
 *
 *         _______6______
 *        /              \
 *    ___2__          ___8__
 *   /      \        /      \
 *  0      _4       7        9
 *        /  \
 *       3    5
 *  
 *  For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. 
 *  Another example is LCA of nodes 2 and 4 is 2, since a node can be a 
 *  descendant of itself according to the LCA definition.
 * */
#include <iostream>
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
    // extend return value of lowestCommonAncestor:
    // nullptr: neither p nor q was found in this subTree;
    // not-null: p or q (or both) is found in this subTree.
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == p) return root;
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        if (l == nullptr) { // neither p nor q found in left SubTree
            return r; // LCA must be in right subTree;
        } 
        if (r == nullptr) { // neither p nor q found in right subTree
            return l; // LCA must be in left subTree;
        }
        return root; // l not-null and r not-null, root is LCA;
    }
};

int main () {
    TreeNode* r = new TreeNode(6);
    r->left = new TreeNode(2);
    r->right = new TreeNode(8);
    r->left->left = new TreeNode(0);
    r->left->right = new TreeNode(4);
    r->left->right->left = new TreeNode(3);
    r->left->right->right = new TreeNode(5);
    r->right->left = new TreeNode(7);
    r->right->right = new TreeNode(9);
    Solution s;
    TreeNode* p = s.lowestCommonAncestor(r, r->left->right->left, r->left);
    cout << p->val << endl;
    return 1;
}
