/*
 * 543. Diameter of Binary Tree
 *
 * Given a binary tree, you need to compute the length of the diameter of the tree. 
 * The diameter of a binary tree is the length of the longest path between any two 
 * nodes in a tree. This path may or may not pass through the root.
 *
 * Example:
 * Given a binary tree 
 *           1
 *          / \
 *         2   3
 *        / \
 *       4   5    
 * Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
 * Note: The length of path between two nodes is represented by the number of edges between them.
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
    // return height of this tree;
    // for each node, calculate it's diameter and compare with current max one, if larger, set.
    int height(TreeNode* root, int& d) {
        if (root == nullptr) return 0;
        int l = height(root->left, d);
        int r = height(root->right, d);
        d = max(d, l+r); // << compare this node's diameter (l+r) with current diameter 
        return max(l, r) + 1; // return this subTree's height(+1 is including root)
    }

    // A diameter must be some path which contains a node that is the highest node;
    // for each node, calculates its diameter and save the maximum one recusively;
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int diameter = -1;
        height(root, diameter);
        return diameter;
    }
};

int main() {
    // [4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2]
    //                                    4
    //                                 /     \
    //                                7      3
    //                                     /     \
    //                                    9       3
    //                                  /    \    /
    //                                 9      7  4
    //                               /      /  \
    //                              6      6   6
    //                            /   \   /    /
    //                           0     6 5    9
    //                            \    /        \
    //                             1   4        2
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(7);
    r->right = new TreeNode(3);

    r->right->left = new TreeNode(9);
    r->right->right = new TreeNode(3);
    r->right->left->left= new TreeNode(9);
    r->right->left->right= new TreeNode(7);
    r->right->right->left = new TreeNode(4);

    r->right->left->left->left = new TreeNode(6);
    r->right->left->right->left = new TreeNode(6);
    r->right->left->right->right= new TreeNode(6);
    
    r->right->left->left->left->left= new TreeNode(0);
    r->right->left->left->left->right= new TreeNode(6);
    
    r->right->left->right->left->left= new TreeNode(5);
    r->right->left->right->right->left= new TreeNode(9);
    r->right->left->right->right->left->right= new TreeNode(2);

    r->right->left->left->left->left->right = new TreeNode(1);
    r->right->left->left->left->right->left= new TreeNode(4);

    Solution s;
    cout << s.diameterOfBinaryTree(r) << endl;
    return 1;
}
