// 
// https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
//
// 1. Initialize current as root 
// 2. While current is not NULL
// ....If current does not have left child
// ........a) Print current's data
// ........b) Go to the right, i.e., current = current->right
// ....Else
// ........a) Make current as right child of the rightmost node in current's left subtree
// ........b) Go to this left child, i.e., current = current->left
//

#ifndef __MORRIS_HPP_INCLUDED__
#define __MORRIS_HPP_INCLUDED__

#include <iostream>
#include <vector>
#include "BSTUtil.hpp"
using namespace std;

class MorrisTraversal {
private:
    TreeNode* mRoot;
public:
    MorrisTraversal(TreeNode* x): mRoot(x) {}
    vector<int> inOrder();
};

vector<int> MorrisTraversal::inOrder() {
    vector<int> res;
    TreeNode* cur = mRoot;
    while (cur) {
        if (cur->left == nullptr) {
            res.push_back(cur->val);
            cur = cur->right;
        } else {
            TreeNode* p = cur->left;
            while (p->right && p->right != cur) p = p->right;
            if (p->right == nullptr) { 
                p->right = cur;
                cur = cur->left;
            } else {  
                // p->right equals cur, meaning we've traversed all the left subtree nodes and 
                // come back from predecessor's(rightmost's right child) right child to cur node;
                p->right = nullptr;  // <<< revert the change
                res.push_back(cur->val);  // visit cur node;
                cur = cur->right;         // go to right subTree;
            }
        }
    }
    return res;
}
#endif
