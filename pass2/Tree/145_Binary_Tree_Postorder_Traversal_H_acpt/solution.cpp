/*
 * 145. Binary Tree Postorder Traversal
 *
 * Given a binary tree, return the postorder traversal of its nodes' values.
 *
 * For example:
 * Given binary tree {1,#,2,3},
 *    1
 *     \
 *      2
 *     /
 *    3
 * return [3,2,1].
 *
 * Note: Recursive solution is trivial, could you do it iteratively?
 * */
#include <iostream>
#include <stack>
#include <vector>
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode* p = root, *lastVisitedNode = nullptr;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                if (p->right && p->right != lastVisitedNode) {
                    p = p->right;
                } else {
                    // visit p
                    s.pop();
                    res.push_back(p->val);
                    lastVisitedNode = p;
                    p = nullptr;
                }
            }
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
    //  11, 9, 33, 19, 12, 98, 20, 8
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
    vector<int> o = s.postorderTraversal(r);
    for (auto x:o) {
        cout << x << ", ";
    }
    cout << endl;
    return 1;
}
