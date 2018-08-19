/*
 * 230. Kth Smallest Element in a BST
 * Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
 *
 * Note: 
 *     You may assume k is always valid, 1<=k<=BST's total elements.
 *
 * Follow up:
 *     What if the BST is modified (insert/delete operations) often and you need to find 
 *     the kth smallest frequently? How would you optimize the kthSmallest routine?
 * */
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

/*** Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int numVisited = 0;
    // inOrder: all the node visited is in increasing order.
    //          left, root, right
    int kthSmallest(TreeNode* root, int k) {
        numVisited = 0;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                // visit p
                p = s.top();
                s.pop();
                if(++numVisited == k)
                    return p->val;
                p = p->right;
            }
        }
    }
};

// 
//                    10
//                 /     \
//                5       20
//              /   \     /  \
//             3     8   15  30
//                  /    /   / \
//                 6    13  25 40
//
int main () {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(8);
    root->left->right->left = new TreeNode(6);

    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right= new TreeNode(30);
    root->right->left->left = new TreeNode(13);
    root->right->right->left = new TreeNode(25);
    root->right->right->right= new TreeNode(40);

    Solution s;
    int v = s.kthSmallest(root, 7);
    assert(v=15);
    v = s.kthSmallest(root, 1);
    assert(v==3);
    v = s.kthSmallest(root, 3);
    assert(v==6);
    v = s.kthSmallest(root, 10);
    assert(v==30);
    
    return 1;
}
