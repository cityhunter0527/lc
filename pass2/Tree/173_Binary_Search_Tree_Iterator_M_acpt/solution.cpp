/*
 * 173. Binary Search Tree Iterator
 *
 * Implement an iterator over a binary search tree (BST). 
 * Your iterator will be initialized with the root node of a BST.
 *
 * Calling next() will return the next smallest number in the BST.
 *
 * Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, 
 * where h is the height of the tree.
 * */

#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

/** Definition for binary tree **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
private:
    stack<TreeNode*> mStk;
public:
    BSTIterator(TreeNode *root) {
        while (root) {
            mStk.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number **/
    bool hasNext() {
        return !mStk.empty();
    }

    // inOrder traversal iteratively
    /** @return the next smallest number */
    int next() {
        assert(!mStk.empty());
        TreeNode* p = mStk.top();
        int ret = p->val;
        mStk.pop();
        p = p->right;
        if (p) {
            while (p) {
                mStk.push(p);
                p = p->left;
            }
        }
        return ret;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 * */
int main() {
    // 
    //         50
    //       /    \
    //      26      101
    //     / \        \
    //    3   36       300
    //       /  \      /  
    //      30   48   156 
    //               /   \
    //             122    256
    //
    TreeNode* r = new TreeNode(50);
    r->left = new TreeNode(26);
    r->right = new TreeNode(101);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(36);
    r->left->right->left = new TreeNode(30);
    r->left->right->right = new TreeNode(48);

    r->right->right = new TreeNode(300);
    r->right->right->left = new TreeNode(156);
    r->right->right->left->left = new TreeNode(122);
    r->right->right->left->right = new TreeNode(256);

    BSTIterator i = BSTIterator(r);
    while (i.hasNext()) 
        cout << i.next() << ", ";
    cout << endl;
    return 1;
}
