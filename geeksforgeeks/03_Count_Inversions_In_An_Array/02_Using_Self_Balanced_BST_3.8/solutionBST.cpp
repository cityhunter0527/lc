/*
 * http://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/
 * */

#include <iostream>
#include <vector>
using namespace std;
class TreeNode {
public: 
    int val; 
    int height; // height of tree rooted at this node
    int size;   // size of tree rooted at this node
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x), height(1), size(1), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /*
     * The essential of this problem is:
     * For every element a[i] in arr from index 0 ... n-1, we need to find all the larger 
     * elements from 0...i-1, and sum them all.
     *
     * This could perfectly be resolved by Binary Search Tree as a BST stores larger/smaller 
     * releationship for all the visited elements. 
     * Only that we need to every node's right subTree's size, so that we could get the increasing inversion 
     * count immediately without traversing the right subTree.
     *
     * 1) Create an empty AVL Tree.  The tree is augmented here 
     *    such that every node also maintains size of subtree 
     *    rooted with this node.
     * 2) Initialize inversion count or result as 0.
     * 3) Iterate from 0 to n-1 and do following for every 
     *    element in arr[i]
     *    a) Insert arr[i] into the AVL Tree.  The insertion 
     *       operation also updates result.  The idea is to
     *       keep counting greater nodes when tree is traversed
     *       from root to a leaf for insertion.  
     * 4) Return result. 
     *
     * When insert a[i], all the nodes from a[0]...a[i-1] has been added to AVL Tree. 
     * While trversing the AVL tree, if a[i] is smaller than the current node, it means 
     * there all the right subTree's nodes are larger than a[i] (since it is a BST), so we 
     * need to increase inverstion count by the 1 (the current node itself) plus # node 
     * of right subTree; 
     * Note we need to do it from root to leaf since we need to make sure all elements between
     * a[0]...a[i-1] are compared.
     * */
    int CountInversions(vector<int>& arr) {
        int invCnt = 0;
        TreeNode* root = nullptr;
        for (int i = 0; i < arr.size(); i++) {
            root = insert(root, arr[i], invCnt);          
        }
        return invCnt;
    }
private:
    // 1. Insert a new node with input value: "key";
    // 2. Return the new root after insertion with rebalance.
    TreeNode* insert(TreeNode* root, int key, int& invCnt) {
        if (root == nullptr) return new TreeNode(key);
        if (key < root->val) {
            root->left = insert(root->left, key, invCnt);
            invCnt += 1 + size(root->right); // <<< all root's right subTree plus root should be counted as inversion;
        }
        else if (key > root->val)
            root->right = insert(root->right, key, invCnt);
        else 
            return root; // <<< duplicate key in BST is now allowed

        root->height = 1 + max(height(root->left), height(root->right));
        root->size = 1 + size(root->left) + size(root->right);

        int balance = getBalance(root);
        // Left left case
        if (balance > 1 && key < root->left->val)
            return rightRotation(root);
        // Right right case
        if (balance < -1 && key > root->right->val)
            return leftRotation(root);
        // Left right case
        if (balance > 1 && key > root->left->val) {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
        // Right Left case
        if (balance < -1 && key < root->right->val) {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
        // if not unbalanced, just return root;
        return root;
    }

    /*
     *    y                       x
     *   / \   Left Rotate       / \
     *  T1  x  ============>    y  T3
     *     / \                 / \
     *    T2  T3              T1  T2
     * */
    TreeNode* leftRotation(TreeNode* n) {
        TreeNode* x = n->right;
        n->right = x->left;
        x->left = n;
        // update height
        n->height = 1 + max(height(n->left), height(n->right));
        x->height = 1 + max(height(x->left), height(x->right));
        // update size
        n->size = 1 + size(n->left) + size(n->right);
        x->size = 1 + size(x->left) + size(x->right);
        return x;
    }

    /*
     *     y                           x
     *    / \    Right Rotate         / \
     *   x   T3  ==============>     T1  y
     *  / \                             / \
     * T1  T2                          T2  T3
     * */
    TreeNode* rightRotation(TreeNode* n) {
        TreeNode* x = n->left;
        n->left = x->right;
        x->right = n;
        // update height
        n->height = 1 + max(height(n->left), height(n->right));
        x->height = 1 + max(height(x->left), height(x->right));
        // update size
        n->size = 1 + size(n->left) + size(n->right);
        x->size = 1 + size(x->left) + size(x->right);
        return x;
    }
    int getBalance(TreeNode* n) {
        return n == nullptr? 0: height(n->left) - height(n->right);
    }

    int size(TreeNode* n) {
        return n == nullptr? 0: n->size;   
    }

    int height(TreeNode* n) {
        return n == nullptr? 0 : n->height;
    }
};

int main() {
    Solution s;
    vector<int> v = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    swap(v[0], v[12]);
    for (auto x:v) 
        cout << x << ", ";
    cout << endl;
    cout << s.CountInversions(v) << endl; // 
    return 0;
}
