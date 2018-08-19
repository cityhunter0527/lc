/*
 * 257. Binary Tree Paths
 * Given a binary tree, return all root-to-leaf paths.

 For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]
* */


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/***  Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // post-order traversal
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>  res;
        if (root == nullptr) return res;
        if (root->left == nullptr && root->right == nullptr) {
            res.push_back(to_string(root->val));
            return res;
        }
        vector<string> l = binaryTreePaths(root->left);
        vector<string> r = binaryTreePaths(root->right);
        string s = to_string(root->val);
        s += "->";
        for (vector<string>::iterator it = l.begin(); it != l.end(); it++) {
            it->insert(0, s);
        }
        for (vector<string>::iterator it = r.begin(); it != r.end(); it++) {
            it->insert(0, s);
        }
        res.insert(res.end(), l.begin(), l.end());
        res.insert(res.end(), r.begin(), r.end());
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->left->right = new TreeNode(5);
    
    Solution s;
    vector<string> out = s.binaryTreePaths(r);

    for (auto x:out)
        cout << x << endl;
    return 1;
}
