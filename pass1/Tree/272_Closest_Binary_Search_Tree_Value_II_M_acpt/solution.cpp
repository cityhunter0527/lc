/*
 * 272. Closest Binary Search Tree Value II
 * Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.
 *
 * Note:
 *     Given target value is a floating point.
 *     You may assume k is always valid, that is: k <= total nodes.
 *     You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
 * 
 * Follow up:
 *     Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?
 *
 * Hint:
 * - Consider implement these two helper functions:
 *     getPredecessor(N), which returns the next smaller node to N.
 *     getSuccessor(N), which returns the next larger node to N.
 * - Try to assume that each node has a parent pointer, it makes the problem much easier.
 * - Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
 * - You would need two stacks to track the path in finding predecessor and successor node separately.
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*** Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                // visit p
                if (res.size() < k) {
                    res.push_back(p->val);
                } else {
                    if (fabs(res[0] - target) > fabs(p->val - target)) {
                        res.erase(res.begin());
                        res.push_back(p->val);
                    } else {
                        return res;
                    }
                }
                p = p->right;
            }
        }
        return res;
    }
};

int main () {
    // F, B, A, D, C, E, G, I, H.
    //          6
    //        /   \
    //       2     7
    //      / \     \
    //     1   4     9
    //        / \   /
    //       3   5 8 
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->right = new TreeNode(9);
    root->right->right->left = new TreeNode(8);
    Solution s;
    vector<int> v = s.closestKValues(root, 5.7, 5);

    for (auto x:v) {
        cout << x << ", ";
    }
    cout << endl;
    return 1;
}
