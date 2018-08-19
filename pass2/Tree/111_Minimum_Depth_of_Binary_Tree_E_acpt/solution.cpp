/*
 * 111. Minimum Depth of Binary Tree
 *
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from 
 * the root node down to the nearest leaf node.
 *
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
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int dl = minDepth(root->left);
        int dr = minDepth(root->right);
        if (!dl && !dr) 
            return 1;

        if (!dl || !dr)
            return max(dl, dr) + 1;
        else
            return min(dl, dr) + 1;
    }
};

int main() {
    return 1;
}
