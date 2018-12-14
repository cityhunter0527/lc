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
    int                 val;
    vector<TreeNode*>   c;
    TreeNode(int x): val(x) {c.clear();}     
};

class BinTreeNode {
public:
    int             val;
    BinTreeNode*    left;
    BinTreeNode*    right;
    BinTreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    BinTreeNode* multi_way_tree_to_bin_tree(TreeNode* root) {
        if (root == nullptr)  return nullptr;
        BinTreeNode* r = new BinTreeNode(root->val);
        if (root->c.size()) r->left = multi_way_tree_to_bin_tree(root->c[0]);
        BinTreeNode* tmp = r->left;
        for (int i = 1; i < root->c.size(); i++) {
            tmp->right = multi_way_tree_to_bin_tree(root->c[i]);
            tmp = tmp->right;
        }
        return r;
    }
};

int main() {
    TreeNode* r =  new TreeNode(1);
    r->c.push_back(new TreeNode(2));
    r->c.push_back(new TreeNode(3));
    r->c.push_back(new TreeNode(4));
    r->c.push_back(new TreeNode(5));
    r->c[1]->c.push_back(new TreeNode(6));
    r->c[1]->c.push_back(new TreeNode(7));
    r->c[1]->c.push_back(new TreeNode(8));

    Solution s;
    BinTreeNode* root = s.multi_way_tree_to_bin_tree(r);
    return 1;
}
