/*
 * 222. Count Complete Tree Nodes
 *
 * Given a complete binary tree, count the number of nodes.
 *
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the last, 
 * is completely filled, and all nodes in the last level are as far 
 * left as possible. It can have between 1 and 2h nodes inclusive at 
 * the last level h.
 * */
#include <iostream>
using namespace std;
/** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//
// h:4
//           x
//        /     \
//      x         x
//    /   \     /   \
//   x     x   x     x  // <<<< total: 2^(h-1) - 1, this layer: 2^(h-2)
//  / \   / 
// x   x x              // <<<< count
class Solution {
public:
    // Iterative:
    //  Binary Search of a tree
    //  nodes = 2^(h-1) - 1 + count // << count is the # of nodes in the lowest level 
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        int h = 0, curh, count = 0;
        TreeNode* p = root;
        while (p) {
            h++;
            p = p->left;
        }
        curh = h - 2;
        p = root;
        // keep finding the lowest layer until we found the edge node p, 
        // curh:-1 means we reach the lowest level
        while (curh >= 0) {
            TreeNode* q = p->left;
            for (int i = 0; i < curh; i++) {
                q = q->right;
            }
            if (q) {
                p = p->right;
                count += (1<<curh);  // <<< the p->left part is a full tree, add the lowest level of this full tree # of nodes which is 2^curh
            } else {
                p = p->left;
            } 
            curh--;
        }
        if (p) count++;
        return (1<<(h-1)) - 1 + count;
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(1);
    r->right = new TreeNode(1);
    r->left->left = new TreeNode(1);
    r->left->right = new TreeNode(1);
    r->left->left->left = new TreeNode(1);
    r->left->left->right = new TreeNode(1);
    r->left->right->left = new TreeNode(1);
    
    r->right->left = new TreeNode(1);
    r->right->right = new TreeNode(1);

    Solution s;
    cout << s.countNodes(r) << endl;;
    return 1;
}
