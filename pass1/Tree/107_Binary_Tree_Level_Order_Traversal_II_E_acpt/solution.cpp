/*
 * 107. Binary Tree Level Order Traversal II
 * Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its bottom-up level order traversal as:
 * [
 * [15,7],
 * [9,20],
 * [3]
 * ]
 * */

#include <iostream>
#include <vector>
#include <deque>
using namespace std;
/** *  * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        deque<TreeNode*> q;
        q.push_back(root);
        q.push_back(nullptr); // separator
        vector<int> tmp;
        while (!q.empty()) {
            TreeNode* t = q.front();
            q.pop_front();
            if (t != nullptr) {
                tmp.push_back(t->val);
                if (t->left) q.push_back(t->left);
                if (t->right) q.push_back(t->right);
            } else {
                if (!q.empty()) q.push_back(nullptr);
                res.insert(res.begin(), tmp);
                tmp.clear();
            }
        }
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(9);
    r->right = new TreeNode(20);
    r->right->left = new TreeNode(15);
    r->right->right = new TreeNode(7);

    Solution s;
    vector<vector<int>> v = s.levelOrderBottom(r);

    for (auto x:v) {
        for (auto y:x) {
            cout << y << ", ";   
        }
        cout << endl;
    }

    return 1;
}
