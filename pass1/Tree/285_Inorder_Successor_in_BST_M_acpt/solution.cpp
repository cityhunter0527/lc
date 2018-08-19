/*
 * 285. Inorder Successor in BST  
 *
 * Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
 * Note: If the given node has no in-order successor in the tree, return null.
 * */

#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode*> s;
        TreeNode* cur = root;
        bool foundP = false;
        while (!s.empty() || cur) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                cur = s.top();
                // visit cur
                if (foundP) 
                    return cur;
                if (cur == p) {
                    foundP = true;
                }
                s.pop();
                cur = cur->right;
            }
        }
        return nullptr;
    }
};

//           5
//      /         \
//     3          10
//    / \        /  
//   1   4      7  
//             /
//            6
//
//  inOrder: 1,3,4,5,6,7,10
int main () {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->left =  new TreeNode(7);
    root->right->left->left =  new TreeNode(6);

    Solution s;
    TreeNode* p = s.inorderSuccessor(root, root->left->left);
    if (p)
        cout<<p->val<<endl;
    else 
        cout << "p is nll" << endl;
    return 1;
}
