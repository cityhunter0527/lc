/*
 * 450. Delete Node in a BST
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. 
 * Return the root node reference (possibly updated) of the BST.
 *
 * Basically, the deletion can be divided into two stages:
 *
 * Search for a node to remove.
 * If the node is found, delete the node.
 * Note: Time complexity should be O(height of tree).
 *
 * Example:
 *
 * root = [5,3,6,2,4,null,7]
 * key = 3
 *
 *     5
 *    / \
 *   3   6
 *  / \   \
 * 2   4   7
 *
 * Given key to delete is 3. 
 * So we find the node with value 3 and delete it.
 *
 * One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
 *
 *      5
 *     / \
 *    4   6
 *   /     \
 *  2       7
 *
 *  Another valid answer is [5,2,6,null,4,null,7].
 *
 *      5
 *     / \
 *    2   6
 *     \   \
 *      4   7
 * */

#include <iostream>
#include <stack>
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
    // 1. find the node, say its left child is L, right child is R.
    // 2. find R's left most child, say mostLeftChild.
    // 3. mostLeftChild->left = L;
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        // 1. find the node: log(n)
        TreeNode* n = nullptr, *pn = nullptr; 
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (p) {
            if (p->val > key) {
                pn = p;
                p = p->left;
            } else if (p->val < key) {
                pn = p;
                p = p->right;
            } else {
                n = p;
                break;
            }
        }

        // node not found;
        if (n == nullptr) return root;
        TreeNode* nL = n->left;
        TreeNode* nR = n->right;
        TreeNode* nodeConnectToPn= nullptr;
        
        if (nR) {
            // 2. 
            TreeNode* leftMostChild = nR;
            while (leftMostChild->left) 
                leftMostChild = leftMostChild->left;
            // 3. 
            leftMostChild->left = nL;
            nodeConnectToPn = nR; 
        } else {
            nodeConnectToPn = nL; 
        }
        
        if (pn) {
            // reconnect parent of n to nL or nR;
            pn->left == n? pn->left = nodeConnectToPn: pn->right = nodeConnectToPn;
        } else {
            root = nodeConnectToPn;
        }
        return root;
    }
};

// 
//         10 
//       /   \
//      5     30
//     / \    / \
//    1   8  15  50
//           /     \
//          12      76
//
int main() {

    TreeNode* r = new TreeNode(10);
    r->left = new TreeNode(5);
    r->right= new TreeNode(30);
    r->left->left= new TreeNode(1);
    r->left->right= new TreeNode(8);
    r->right->left= new TreeNode(15);
    r->right->right= new TreeNode(50);
    r->right->left->left= new TreeNode(12);
    r->right->right->right= new TreeNode(76);
    Solution s;
    TreeNode* newRoot = s.deleteNode(r, 30);
    return 1;
}
