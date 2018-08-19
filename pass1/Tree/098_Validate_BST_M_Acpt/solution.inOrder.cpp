/*
 * 98. Validate Binary Search Tree
 *
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 * Example 1:
 *     2
 *    / \
 *   1   3
 *  Binary tree [2,1,3], return true.
 *  
 *  Example 2:
 *     1
 *    / \
 *   2   3
 *  Binary tree [1,2,3], return false.
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
};

class Solution {
public:
    // In-Order traversal of BST should always be increasing
    bool isValidBST(TreeNode* root) {
        if (root == nullptr)
            return true;

        // iterative inOrder traversal and stove val to v
        stack<TreeNode*> s;
        vector<int> v;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                v.push_back(p->val);
                p = p->right;
            }
        }

        // now make sure it is in increasing order
        int last = v[0];
        for (int i = 1; i < v.size(); i++) {
            if (last >= v[i])
                return false;
            last = v[i];
        }
        return true;
    }
};

int main () {
    //[2147483647]
    return 1;
}
