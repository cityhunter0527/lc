/*
 * 337. House Robber III
 * The thief has found himself a new place for his thievery again. There is only one entrance 
 * to this area, called the "root." Besides the root, each house has one and only one parent house. 
 * After a tour, the smart thief realized that "all houses in this place forms a binary tree". 
 * It will automatically contact the police if two directly-linked houses were broken into on the same night.
 *
 * Determine the maximum amount of money the thief can rob tonight without alerting the police.
 *
 * Example 1:
 *      3
 *     / \
 *    2   3
 *     \   \
 *      3   1
 *  
 *  Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
 *
 *  Example 2:
 *      3
 *     / \
 *    4   5
 *   / \   \
 *  1   3   1
 * Maximum amount of money the thief can rob = 4 + 5 = 9.
 *
 * */

#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    /* 
     * dfs:
     *     rob_root = max(rob_L + rob_R, no_rob_L + no_nob_R + root.val)
     *     no_rob_root = rob_L + rob_R
     * */
    pair<int, int> dfs(TreeNode* root) {
        // dp.first: rob_root
        // dp.right: non_rob_root
        pair<int, int> dp = make_pair(0,0);
        if (root){
            pair<int, int> dp_L = dfs(root->left);
            pair<int, int> dp_R = dfs(root->right);
            dp.second = dp_L.first + dp_R.first;
            dp.first = max(dp.second + dp_L.second + dp_R.second + root->val);
        }
        return dp;
    }

public:
    int rob(TreeNode* root) {
        return dfs(root).first;
    }
};

int main () {
    // [4,1,null,2,null,3]
#if 0
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(1);
    r->left->left = new TreeNode(2);
    r->left->left->right = new TreeNode(3);
    class Solution s;
    int v = s.rob(r);
    assert (v == 7);
#endif
    //[3,100,10,5,5,200,null,null, 200]
    //                   3
    //                /     \
    //              100     10
    //              / \     / 
    //             5   5   200
    //              \
    //              200
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(100);
    r->right = new TreeNode(10);
    r->left->left = new TreeNode(5);
    r->left->right = new TreeNode(5);
    r->left->left->right = new TreeNode(200);

    r->right->left = new TreeNode(200);
    class Solution s;
    int v = s.rob(r);
    assert (v == 500);

    return 1;
}
