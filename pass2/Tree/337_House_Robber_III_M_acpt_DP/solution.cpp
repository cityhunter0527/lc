/*
 * 337. House Robber III
 *
 * The thief has found himself a new place for his thievery again. 
 * There is only one entrance to this area, called the "root." 
 * Besides the root, each house has one and only one parent house. 
 * After a tour, the smart thief realized that "all houses in this 
 * place forms a binary tree". 
 *
 * It will automatically contact the police if two directly-linked 
 * houses were broken into on the same night.
 *
 * Determine the maximum amount of money the thief can rob tonight without alerting the police.
 *
 * Example 1:
 *      3
 *     / \
 *    2   3
 *     \   \
 *      3   1
 *  Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
 *  Example 2:
 *               3
 *              / \
 *             4   5
 *            / \   \
 *           1   3   1
 *  Maximum amount of money the thief can rob = 4 + 5 = 9.
 * */

#include <iostream>
#include <deque>
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
#if 0
    // assuming all val is > 0; 
    // recursive solutoin;
    int rob(TreeNode* root) {
        if (root == nullptr) return 0;
        int l = rob(root->left);
        int r = rob(root->right);
        int ll = 0, rr = 0;
        if (root->left) ll = rob(root->left->left) + rob(root->left->right);
        if (root->right) rr = rob(root->right->left) + rob(root->right->right);
        return max(ll + rr + root->val, l + r);
    }
#endif
    // A lot of repeated calculaitons in above solutoin 
    // using DP to avoid
    int rob(TreeNode* root) {
        vector<int> res = robSub(root);
        return max(res[0], res[1]);
    }

    // return value means for each root called with robSum:
    // vector[0]: max value with root not robbed
    // vector[1]: max value with root robbed 
    vector<int> robSub(TreeNode* root) {
        if (root == NULL) {
            return vector<int>(2,0);
        }

        vector<int> left = robSub(root->left);
        vector<int> right = robSub(root->right);

        vector<int> res(2,0);
        res[0] = max(left[0], left[1]) + max(right[0], right[1]);
        res[1] = root->val + left[0] + right[0];

        return res;
    }
};

int main() {
    // 
    // [4, 1, null, 2, null, 3]
    //          4
    //         /
    //        1
    //       /
    //      2
    //     /
    //    3
    //
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(1);
    r->left->left = new TreeNode(2);
    r->left->left->left = new TreeNode(3);
    
    Solution s;
    cout << s.rob(r) << endl;
    return 1;
}
