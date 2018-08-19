#include <vector>
#include <iostream>
using namespace std;

enum Color {
    BLACK,
    RED,
}; 

class TreeNode {
public:
    int val;
    Color color;
    TreeNode* left, *right, *parent;
    TreeNode(int x):val(x), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

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
private:
    TreeNode* root;
protected:
    void leftRotate(TreeNode*);
    void rightRotate(TreeNode*);
    TreeNode* BSTInsert(TreeNode*, TreeNode*); 
    TreeNode* BSTLookup(TreeNode*, const int key); 
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
    void insert(const int key); // << geeksforgeeks
    void remove(const int key); // << <<Introduction to Algorithms>>
    vector<int> inOrder();
    vector<int> levelOrder();
    vector<vector<string>> printTree();
    TreeNode* getRoot() {return root;}
};

