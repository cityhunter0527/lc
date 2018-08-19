/*
 *  113. Path Sum II
 *  Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if (!root) return res;
        if (root->val == sum && !root->left && !root->right) {
            res.push_back(vector<int>{root->val});
            return res;
        }
        // do it for left child
        vector<vector<int>> resL = pathSum(root->left, sum - root->val);
        // insert itself in the begining of every result 
        for (vector<vector<int>>::iterator it = resL.begin(); it != resL.end(); ++it) {
            it->insert(it->begin(), root->val);
        }
        // do it for right child
        vector<vector<int>> resR = pathSum(root->right, sum - root->val);
        // insert itself in the begining of every result 
        for (vector<vector<int>>::iterator it = resR.begin(); it != resR.end(); ++it) {
            it->insert(it->begin(), root->val);
        }

        // merge resL and resR to res;
        if (resL.size()>0) res.insert(res.end(), resL.begin(), resL.end());
        if (resR.size()>0) res.insert(res.end(), resR.begin(), resR.end());
        return res;
    }
};

int main () {
    /*
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
     * */

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
    vector<vector<int>> o = s.pathSum(r, 22);
    for (auto x:o) {
        cout << "[ ";
        for (auto y:x) {
            cout << y << ", ";
        }
        cout << " ]" << endl;
    }
    cout << endl;
    return 1;
}
