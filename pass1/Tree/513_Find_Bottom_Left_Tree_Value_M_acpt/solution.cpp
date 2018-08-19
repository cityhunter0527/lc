/*
 * 513. Find Bottom Left Tree Value
 *
 * Given a binary tree, find the leftmost value in the last row of the tree.
 *
 * you may assume root is not null
 *
 * Example 1:
 * Input:
 *
 *     2
 *    / \
 *   1   3
 *
 * Output:
 * 1
 * 
 * Example 2: 
 * Input:
 *
 *            1
 *           / \
 *          2   3
 *         /   / \
 *        4   5   6
 *           /
 *          7
 *
 * Output:
 * 7
 * */

#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // level order traversal
    int findBottomLeftValue (TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        int btmLeft = root->val;
        bool flag = true;
        while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop();
            if (p == nullptr) {
                if (!q.empty()) q.push(nullptr);
                flag = true;
            } else {
                if (p->left) q.push(p->left);
                if (p->right) q.push(p->right);
                if (flag) {
                    btmLeft = p->val;
                    flag = false;
                }
            }
        }
        return btmLeft;
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->right->left = new TreeNode(5);
    r->right->right = new TreeNode(6);
    Solution s;
    int out = s.findBottomLeftValue(r);
    cout << out << endl;

    return 1;
}
