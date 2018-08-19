/*
 * 257. Binary Tree Paths
 * Given a binary tree, return all root-to-leaf paths.
 *
 * For example, given the following binary tree:
 *
 *    1
 *  /   \
 * 2     3
 *  \
 *   5
 * All root-to-leaf paths are:
 *["1->2->5", "1->3"]
 * */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
/** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    void helper(TreeNode* root, string path, vector<string>& res) {
        path.append(to_string(root->val));
        if (root->left == nullptr && root->right == nullptr)
            res.push_back(path);
        else  {
            if (root->left != nullptr )helper(root->left, path + "->", res);
            if (root->right != nullptr )helper(root->right, path + "->", res);
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (root == nullptr) return res;
        string path;
        helper(root, path, res);
        return res;
    }
};

int main () {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->right = new TreeNode(5);

    Solution s;
    vector<string> v = s.binaryTreePaths(r);
    for (auto x:v) {
        cout << x << endl;
    }
    return 1;
}
