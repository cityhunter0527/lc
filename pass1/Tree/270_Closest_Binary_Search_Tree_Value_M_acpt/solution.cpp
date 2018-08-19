/* 
 * 270. Closest Binary Search Tree Value
 *
 * Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
 *
 * Note:
 * Given target value is a floating point.
 * You are guaranteed to have only one unique value in the BST that is closest to the target.
 * */
#include <iostream>
#include <stack>
#include <cfloat>
#include <algorithm>
#include <limits>
using namespace std;
/***  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    double delta = numeric_limits<double>::max();
    int res = 0;
    // inOrder Traversal
    int closestValue(TreeNode* root, double target) {
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                //visit p
                double tmp = fabs(target - p->val);
                if (delta >= tmp) {
                    delta = tmp;
                    res = p->val;
                } else {
                    return res;
                }
                p = p->right;
            }
        }

        return res;
    }
};

int main () {
    return 1;
}
