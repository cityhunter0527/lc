/** 
 * 129. Sum Root to Leaf Numbers
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 *
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
 *
 * Find the total sum of all root-to-leaf numbers.
 *
 * For example,
 *
 *     1
 *    / \
 *   2   3
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 *
 * Return the sum = 12 + 13 = 25.
 * */

#include <iostream>
#include <vector>
#include <cassert>
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
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
    int dfs(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        if (root->left==0 && root->right == 0)
            return sum*10+ root->val;
        return dfs(root->left, root->val+sum*10) + 
            dfs(root->right, root->val+sum*10);
    }
    
};
int main () {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    Solution s;
    int v = s.sumNumbers(root);
    cout << v << endl;
    assert(v == 25);

    return 1;
} 
