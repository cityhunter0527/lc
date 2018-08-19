/*
 * 144. Binary Tree Preorder Traversal
 * Given a binary tree, return the preorder traversal of its nodes' values.
 *
 * For example:
 * Given binary tree {1,#,2,3},
 *    1
 *     \
 *     2
 *    /
 *   3
 *  return [1,2,3].
 *
 *  Note: Recursive solution is trivial, could you do it iteratively?
 * */

#include <iostream>
#include <vector>
#include <stack>
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            // visit this node
            TreeNode* p = s.top();
            s.pop();
            res.push_back(p->val);
            if (p->right)
                s.push(p->right);
            if (p->left)
                s.push(p->left);
        }
        return res;
    }
};

int main() {
    //  
    //            8
    //        /       \
    //       12         20
    //      /  \        /
    //     11   19     98
    //          / \
    //         9   33
    //
    //  PreOrder: 8, 12, 11, 19, 9, 33, 20, 98
    //      
    TreeNode* r = new TreeNode(8);
    r->left = new TreeNode(12);
    r->right = new TreeNode(20);
    r->left->left = new TreeNode(11);
    r->left->right = new TreeNode(19);
    r->left->right->left = new TreeNode(9);
    r->left->right->right = new TreeNode(33);
    r->right->left = new TreeNode(98);
    
    Solution s;
    vector<int> o = s.preorderTraversal(r);
    for (auto x:o)
        cout << x << ", ";
    cout << endl;
    return 1;
}
