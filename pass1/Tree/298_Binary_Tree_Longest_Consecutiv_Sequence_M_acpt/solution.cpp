/*
 *  298. Binary Tree Longest Consecutive Sequence
 *  Given a binary tree, find the length of the longest consecutive sequence path.
 *
 *  The path refers to any sequence of nodes from some starting node to any node in 
 *  the tree along the parent-child connections. The longest consecutive path need to be 
 *  from parent to child (cannot be the reverse).
 *
 *  For example,
 *     1
 *      \
 *       3
 *      / \
 *     2   4
 *          \
 *           5
 *  Longest consecutive sequence path is 3-4-5, so return 3.
 *       2
 *        \
 *         3
 *        / 
 *       2    
 *      / 
 *     1
 *  Longest consecutive sequence path is 2-3,not 3-2-1, so return 2. 
 *
 * */

#include <iostream>
#include <cassert>
using namespace std;

/*** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int res = 0;
    int longestConsecutive(TreeNode* root) { 
        if (!root) return 0;
        dfs(root);
        return res;
    }
    
    // postOrder traversal:
    // dfs(root):
    //     0. if root is null, return 0;
    //     1. Get lc for left child.
    //     2. Get lc for right child.
    //     3. get max of curLen, lcLeft and lcRight.
    //        - need to do +1 for left/right accordingly if val of root and left/right are consecutive.
    //     4. Update gloable result 'res'.
    //     5. return lcCur in step #3.
    int dfs(TreeNode* root) {
        if (root == nullptr) return 0;
        int lcLeft = 0, lcRight = 0;
        int lcCur = 1;
        lcLeft = dfs(root->left);
        lcRight = dfs(root->right);
        if (root->left && root->val + 1 == root->left->val)
            lcCur = max(lcCur, lcLeft+1);
        if (root->right && root->val + 1 == root->right->val)
            lcCur = max(lcCur, lcRight+1);
        // update gloable result
        res = max(res, lcCur);
        return lcCur;
    } 
};

int main() {
    // 
    // [1,2,3,4,null,null,4]
    //             1
    //          /     \
    //         2        3
    //       /            \
    //      4              4 
    //
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->right =  new TreeNode(4);
    Solution s;
    int v = s.longestConsecutive(root);
    cout<<v<<endl;
    assert(v==2);
    return 1;
}
