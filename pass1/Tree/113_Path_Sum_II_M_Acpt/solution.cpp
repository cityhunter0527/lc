/*
 * 113 Path Sum II
 *
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
 *
 * For example:
 * Given the below binary tree and sum = 22,
 *               5
 *              / \
 *             4   8
 *            /   / \
 *           11  13  4
 *          /  \    / \
 *         7    2  5   1
 * return
 * [
 * [5,4,11,2],
 * [5,8,4,5]
 * ]
 * */
#include <iostream>
#include <vector>
using namespace std;
/*** Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//TODO: Try to solve it iteratively?
class Solution {
public:
    bool isleaf(TreeNode* p) {
        return (p->left == nullptr) && (p->right == nullptr);
    }
    // preOrder
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if (root == NULL) return res;
        if (root->val == sum && isleaf(root)) {
            vector<int> v = {root->val};
            res.push_back(v);
            return res;
        }
        vector<vector<int>> vL = pathSum(root->left, sum - root->val);
        vector<vector<int>> vR = pathSum(root->right, sum - root->val);
        // Build Result
        // Combine vL and vR into res.
        res.reserve(vL.size() + vR.size());
        res.insert(res.end(), vL.begin(), vL.end());
        res.insert(res.end(), vR.begin(), vR.end());
        // for each path in res, insert root to head of each path.
        for (auto x = res.begin(); x < res.end(); x++) {
            x->insert(x->begin(), root->val);
        }
        return res;
    }
};

int main() {
#if 0
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);

    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->left = new TreeNode(5);
    root->right->right->right = new TreeNode(1);
#endif
#if 0
    TreeNode* root = new TreeNode(-2);
    root->right = new TreeNode(-3);
#endif
    // [1,-2,-3,1,3,-2,null,-1]
    // -1
    // result: [[1,-2,1,-1]]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(-2);
    root->right = new TreeNode(-3);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->left->left->left = new TreeNode(-1);

    root->right->left = new TreeNode(-2);

    Solution s;
    vector<vector<int>> v = s.pathSum(root, -1);
    for (auto x : v) {
        for (auto y : x) {
            cout << y << ", ";
        }
        cout << endl;
    }
    return 1;
}
