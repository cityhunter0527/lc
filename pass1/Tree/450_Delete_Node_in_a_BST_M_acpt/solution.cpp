/*
 * 450. Delete Node in a BST
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
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
 * Given key to delete is 3. So we find the node with value 3 and delete it.
 *
 * One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
 *
 *      5
 *     / \
 *    4   6
 *   /     \
 *  2       7
 *
 * Another valid answer is [5,2,6,null,4,null,7].
 *
 *       5
 *      / \
 *     2   6
 *      \   \
 *       4   7
 * */
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // recursive
    TreeNode* deleteNodeRecursive(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val > key) {
            // node in left subTree;
            root->left = deleteNodeRecursive(root->left, key);   
        } else if (root->val < key) {
            // node in right subTree;
            root->right = deleteNodeRecursive(root->right, key);   
        } else {
            if (root->left == nullptr) 
                return root->right;
            if (root->right == nullptr)
                return root->left;

            // set root as it's right sub Tree's left most node's value.
            TreeNode* tmp = root->right;
            while (tmp) {
                if (tmp->left == nullptr) {
                    root->val = tmp->val;
                    root->right = deleteNodeRecursive(root->right, tmp->val);
                    break;
                } else
                    tmp = tmp->left;
            }
        }
        return root;
    }

    // non-recursive
    TreeNode* deleteNode(TreeNode* root, int key){
        if (root == nullptr) return root;
        TreeNode* p = root;
        TreeNode* parent = nullptr;
        while (p) {
            if (p->val == key) {
                if (p->left == nullptr) {
                    // p's left is null
                    if (parent == nullptr) root = root->right;
                    else if (parent->left == p)
                        parent->left = p->right;
                    else 
                        parent->right = p->right;
                } else if (p->right == nullptr) {
                    // p's right is null
                    if (parent == nullptr) root = root->left;
                    else if (parent->left == p)
                        parent->left = p->left;
                    else 
                        parent->right = p->left;
                } else {
                    // neither left nor right is null.
                    // set new p as p's right sub tree's left mode node's value
                    TreeNode* tmp = p->right;
                    TreeNode* ptmp = nullptr;
                    while (tmp) { 
                        if (tmp->left == nullptr) {
                            if (ptmp == nullptr) 
                                p->right = tmp->right;
                            else 
                                ptmp->left = tmp->right;
                            p->val = tmp->val;
                            break;
                        } else {
                            ptmp = tmp;
                            tmp = tmp->left;
                        }
                    }
                }
                break;
            } else {
                parent = p;
                if (p->val > key) {
                    p = p->left;
                } else {
                    p = p->right;
                }
            }
        }
        return root;
    }
};

int main() {
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(3);
    r->right = new TreeNode(6);
    r->left->left = new TreeNode(2);
    r->left->right = new TreeNode(4);
    r->right->right = new TreeNode(7);

    Solution s;
    TreeNode* newR = s.deleteNode(r, 3);

    return 1;
}
