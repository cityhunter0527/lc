/*
 * 129. Sum Root to Leaf Numbers
 *
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
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
using namespace std;
/** *  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
private:
public:
    // top-down manner;
    // preOrder
    int dfs(TreeNode* root, int sum) {
        if (!root) return 0;
        if (!root->left && !root->right) 
            return sum*10 + root->val;
        return dfs(root->left, sum*10+root->val) + dfs(root->right, sum*10+root->val);
    }
    int sumNumbers(TreeNode* root) {
        if (!root) return 0;
        return dfs(root, 0);
        //return dfs(root->left, sum*10) + dfs(root->right, sum*10);
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->left->right = new TreeNode(5);
    Solution s;
    cout << s.sumNumbers(r) << endl;
    return 1;
}
