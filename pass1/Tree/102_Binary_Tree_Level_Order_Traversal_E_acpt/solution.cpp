/*
 * 102. Binary Tree Level Order Traversal
 *
 * Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its level order traversal as:
 * [
 * [3],
 * [9,20],
 * [15,7]
 * ]
 * */

#include <iostream>
#include <vector>
#include <deque>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;
        vector<int> tmp;
        deque<TreeNode*> q;
        q.push_back(root);
        q.push_back(nullptr);
        while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop_front();
            if (p != nullptr) {
                tmp.push_back(p->val);
                if (p->left)
                    q.push_back(p->left);
                if (p->right)
                    q.push_back(p->right);
            } else {
                if (!q.empty())
                    q.push_back(nullptr);
                res.push_back(tmp);
                tmp.clear();
            }
        }
        return res;
    }
};

int main() {
#if 0
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(9);
    r->right = new TreeNode(20);
    r->right->left = new TreeNode(15);
    r->right->right = new TreeNode(7);
#endif
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    Solution s;
    vector<vector<int>> res = s.levelOrder(r);
    for (auto x:res) {
        for (auto y:x)
            cout<<y<<",";
        cout << endl;
    }

    return 1;
}
