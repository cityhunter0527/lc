/*
 * 226. Invert Binary Tree
 * Invert a binary tree.
 *
 *      4
 *    /   \
 *   2     7
 *  / \   / \
 * 1   3 6   9
 * to
 *      4
 *    /   \
 *   7     2
 *  / \   / \
 * 9   6 3   1
 * */

#include <iostream>
#include <queue>
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
    // interative:
    // level-Order traversal
    // top-down manner: for every node, swap its left with right
    TreeNode* invertTreeIterative(TreeNode* root) {
        if (root == nullptr) return root;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop();
            swap(p->left, p->right); // do revert
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        return root;
    }
    // recurive: post order traversal
    // bottom-up manner
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;
        invertTree(root->left);
        invertTree(root->right);
        swap(root->left, root->right);
        return root;
    }
};

// 
//                  10
//                /    \
//               6      40
//              / \    /  \
//             2   8  21  62
//  
int main() {
    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(6);
    r->right = new TreeNode(40);
    r->left->left = new TreeNode(2);
    r->left->right = new TreeNode(8);
    r->right->left = new TreeNode(21);
    r->right->right= new TreeNode(62);
    
    Solution s;
    s.invertTreeIterative(r);
    return 1;
}
