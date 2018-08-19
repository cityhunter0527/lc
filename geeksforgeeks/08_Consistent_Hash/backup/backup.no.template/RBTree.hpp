#ifndef __RBTREE_HPP__
#define __RBTREE_HPP__

#include <vector>
#include <iostream>
using namespace std;

enum Color {
    BLACK,
    RED,
}; 

typedef unsigned long KEY_TYPE;

// 
// Red-black Tree Properties:
// 1. Every node is either red or black
// 2. The root is black
// 3. Every null node is black
// 4. If a node is red, then both its children are black
// 5. For each node, all simple paths from this node to descendant 
//    leaves contain the same number of black nodes
//
class RBTree {
    class TreeNode {
        public:
            KEY_TYPE val;
            Color color;
            void* data;
            TreeNode* left, *right, *parent;
            TreeNode(KEY_TYPE x, void* blob):val(x), color(RED), data(blob), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    TreeNode* root;
protected:
    void leftRotate(TreeNode*);
    void rightRotate(TreeNode*);
    TreeNode* BSTInsert(TreeNode*, TreeNode*); 
    TreeNode* BSTLookup(TreeNode*, const KEY_TYPE key); 
    // Fix red-black properties after insert
    void fixViolation(TreeNode* x);
    // Replace subtree u as a child of u's parent with another subtree v;
    void transplant(TreeNode* u, TreeNode* v);
    // Fix red-black properties
    void removeFixup(TreeNode* x, TreeNode* px);
    // Return minumum node in subtree rooted at u;
    TreeNode* minimum(TreeNode* u);
public:
    RBTree():root(nullptr) {};
    void insert(const KEY_TYPE key, void* data); // << geeksforgeeks
    void remove(const KEY_TYPE key); // << <<Introduction to Algorithms>>
    vector<int> inOrder();
    vector<int> levelOrder();
    vector<vector<string>> printTree();
    TreeNode* getRoot() {return root;}
    void* lookup(const KEY_TYPE key) {
        if (root == nullptr) return nullptr;
        TreeNode* x = root;
        TreeNode* node = nullptr;
        while (x != nullptr) {
            if (key <= x->val) {
                node = x;
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return node ? node->data : minimum(root)->data;
    } 

    void* search(const KEY_TYPE key) {
        TreeNode* x = BSTLookup(root, key);
        if (x)
            return x->data;
        else
            return nullptr;
    }
};
#endif
