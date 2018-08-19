/*
 * 236. Lowest Common Ancestor of a Binary Tree
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 *
 * According to the definition of LCA on Wikipedia: 
 * "The lowest common ancestor is defined between two nodes v and w as the lowest node in T 
 * that has both v and w as descendants (where we allow a node to be a descendant of itself)."
 *
 *         _______3______
 *        /              \
 *    ___5__          ___1__
 *   /      \        /      \
 *  6      _2_       0       8
 *        /   \
 *       7     4
 * For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. 
 * Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
 * */

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

/**  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // preOrder
    // 1. if root equals to p or q, return root;
    //    if root is null, return null. (meaning we are done with this subTree, and no p or q found).
    // 2. else 
    //         get l = lowestCommonAncestor with left child subTree.
    //         get r = lowestCommonAncestor with right child subTree.
    // 3. if l == null, meaning no p or q found in left subTree.
    //    return r (p, q must be in right subTree);
    // 4. if r == null, meaning no p or q found in right subTree. 
    //    return l (p, q must in left subTree);
    // 5. if r != null && l != null, it means, found p or q in left subTree, and found p or q in right subTree, 
    //    then return root.
    //    
     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;    
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        if (l == nullptr)
            return r;
        if (r == nullptr)
            return l;
        return root;
    }
    };

int main () {
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(5);
    r->right = new TreeNode(1);

    r->left->left = new TreeNode(6);
    r->left->right = new TreeNode(2);

    r->left->right->left = new TreeNode(7);
    r->left->right->right = new TreeNode(4);

    r->right->left = new TreeNode(0);
    r->right->right = new TreeNode(8);

    Solution s;
    TreeNode* p = s.lowestCommonAncestor(r, r->left->right->left, r->left); // 7, 5
    assert (p == r->left); // 5
    p = s.lowestCommonAncestor(r, r->left->left, r->left->right->left);  // 6, 7
    assert (p == r->left); // 5
    p = s.lowestCommonAncestor(r, r->left->left, r->right->right);  // 6, 8
    assert (p == r); // 3
    p = s.lowestCommonAncestor(r, r->right, r->right->right);  // 1, 8
    assert (p == r->right); // 1
    return 1;
}
