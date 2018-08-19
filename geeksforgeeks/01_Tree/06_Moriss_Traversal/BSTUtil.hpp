#ifndef __BSTUTIL_HPP_INCLUDED__
#define __BSTUTIL_HPP_INCLUDED__

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <ctime>
#include <unordered_set>
#include <assert.h>
#include <algorithm>
#include <sstream>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class BinarySearchTree {
private: 
    TreeNode* mRoot;
protected:
    TreeNode* insert(TreeNode* x, int k);
    TreeNode* remove(TreeNode* x, int k);
    bool search(TreeNode* x, int k);
    int getMin(TreeNode* x);
public:
    BinarySearchTree():mRoot(nullptr) {}
    BinarySearchTree(TreeNode* x):mRoot(x) {}
    void insert(int key) { mRoot = insert(mRoot, key); }
    void remove(int key) { mRoot = remove(mRoot, key); };
    TreeNode* getTree() { return mRoot; };
    vector<int> inOrder();
    bool search(int k) {return search(mRoot, k);}
};

class BSTUtil {
protected:
    template <typename Iterator>
    TreeNode* sortedArrayToBST(Iterator start, Iterator end);
    void serialize(ostringstream& o, TreeNode* x);
    TreeNode* deserialize(istringstream& i);
public:
    // deserialize binary tree from string
    TreeNode* deserialize(string data);
    // serialize binary tree to string
    string serialize(TreeNode* root);
    // Generate unique random keys
    // Parameters: 
    // num: the number of keys need to be generated;
    // range: the upper limit of the keys. All keys will be less than range;
    vector<int> getUniqueRandomKeys(int num, int range = 100);
    // convert sorted array to balanced BST;
    BinarySearchTree* sortedArrayToBST(vector<int>& arr);
    // convert array to BST;
    BinarySearchTree* arrayToBST(vector<int>& arr);
};

#endif
