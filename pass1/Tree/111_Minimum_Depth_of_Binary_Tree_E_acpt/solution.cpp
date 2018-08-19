/*
 * 111. Minimum Depth of Binary Tree
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
 *
 * */

#include <iostream>
#include <climits>
using namespace std;
/** *  * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int l = minDepth(root->left);
        int r = minDepth(root->right);
        if (!l && !r) 
            return 1;
        if (min(l,r) == 0) 
            return 1 + max(l,r);
        else 
            return 1 + min(l,r);
    }
};

// 
//                 1
//               /   \
//             2       3
//            / \
//           4   5    
//
//
int main () {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->left = new TreeNode(4);
    r->left->right = new TreeNode(5);
    Solution s;
    int v = s.minDepth(r);
    cout<<v<<endl;
    return 1;
}
