/* 
 * 173. Binary Search Tree Iterator
 * Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
 *
 * Calling next() will return the next smallest number in the BST.
 *
 * Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
 * */

#include <iostream>
#include <stack>
using namespace std;
/** Definition for binary tree */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class BSTIterator {
public:

    // inOrder Traversal
    BSTIterator(TreeNode *root) {
        if (root) {
            s.push(root);
        
            TreeNode* p = root->left;
            while (p) {
                s.push(p);
                p = p->left;
            }
        } 
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* p = s.top();
        s.pop();
        int v = p->val;
        p = p->right;
        while (p) {
            if (p) {
                s.push(p);
                p = p->left;
            }
        }
        return v;
    }
private:
    stack<TreeNode*> s;
};

/*
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 *
 *
 *                  5
 *                /   \
 *              3       8
 *             / \     / \
 *            2   4   7   9
 *           /       /
 *          1       6
 * */
int main () {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);

    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->left->left->left = new TreeNode(1);

    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->right->left->left = new TreeNode(6);
    
    BSTIterator i = BSTIterator(nullptr);
    while (i.hasNext()) {
        cout<< i.next();
    }

    return 1;
}


