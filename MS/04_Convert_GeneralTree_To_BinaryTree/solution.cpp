/* 
 * Multi-Tree: each node has 0 ~ N nodes (N > 2).
 * Binary Tree: each node has 0 ~ 2 nodes
 *
 * Convert Rule:
 * 1. for a given node in multi-tree, it is first child should be corresponding BT nodes' left child.
 * 2. for any right brother node, it should be corresponding BT nodes' left child's right child.
 *
 *      1                         1
 *  /  / \  \                    /
 * 2  3   4  5   ====>          2
 *   /|\                          \
 *  6 7 8                          3 
 *                                /  \
 *                               6     4
 *                                \      \
 *                                 7      5
 *                                  \
 *                                   8  
 *
 * */

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int val;
    vector<TreeNode*> children;
    TreeNode(int x): val(x) {children.clear();}     
};

class BinTreeNode {
public:
    int val;
    BinTreeNode* left;
    BinTreeNode* right;
    BinTreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    BinTreeNode* MultiTreeToBinTree(TreeNode* root) {
        if (!root) return nullptr;
        BinTreeNode* res = new BinTreeNode(root->val);
        TreeNode* firstChild = nullptr;

        if (root->children.size() > 0)
            firstChild = root->children[0];
        if (firstChild) {
            res->left = MultiTreeToBinTree(firstChild);
            BinTreeNode* tmp = res->left;
            for (int i = 1; i < root->children.size(); i++) {
                tmp->right = MultiTreeToBinTree(root->children[i]);
                tmp = tmp->right;
            }
        } 
        return res;
    }
};

int main() {
    TreeNode* r =  new TreeNode(1);
    r->children.push_back(new TreeNode(2));
    r->children.push_back(new TreeNode(3));
    r->children.push_back(new TreeNode(4));
    r->children.push_back(new TreeNode(5));
    r->children[1]->children.push_back(new TreeNode(6));
    r->children[1]->children.push_back(new TreeNode(7));
    r->children[1]->children.push_back(new TreeNode(8));

    Solution s;
    BinTreeNode* root = s.MultiTreeToBinTree(r);
    return 1;
}
