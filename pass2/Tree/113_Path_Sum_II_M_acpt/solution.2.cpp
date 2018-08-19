/*
 * 113 Path Sum II
 Given a binary tree and a sum, find all root-to-leaf paths where 
 each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]
*
 *
 * */


#include <iostream>
#include <vector>
using namespace std;
/** * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // 
    // pre-order
    //
    // path: a vector of int which stores val from root to current node "n";
    //
    void dfs(TreeNode* n, int sum, vector<vector<int>>& res, vector<int>& path) {
        if (!n) return;
        path.push_back(n->val);
        if (!n->left && !n->right) {
            if (n->val == sum) {
                res.push_back(path);
            } 
            path.pop_back();
            return;
        } 
        dfs(n->left, sum-n->val, res, path);
        dfs(n->right, sum-n->val, res, path);
        path.pop_back();
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(root, sum, res, path);
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(4);
    r->right = new TreeNode(8);
    r->left->left = new TreeNode(11);
    r->left->left->left = new TreeNode(7);
    r->left->left->right = new TreeNode(2);

    r->right->left = new TreeNode(13);
    r->right->right = new TreeNode(4);
    r->right->right->left = new TreeNode(5);
    r->right->right->right = new TreeNode(1);

    Solution s;
    vector<vector<int>> v = s.pathSum(r, 22);

    for (auto x:v){
        for (auto y:x)
            cout << y << ", ";
        cout << endl;
    }

    return 1;
}
