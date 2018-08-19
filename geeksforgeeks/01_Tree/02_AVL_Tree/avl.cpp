/*
 * Steps to follow for insertion:
   
   Let the newly inserted node be w
1) Perform standard BST insert for w.
2) Starting from w, travel up and find the first unbalanced node. 
   Let z be the first unbalanced node, y be the child of z that comes on 
   the path from w to z and x be the grandchild of z that comes on the path from w to z.
3) Re-balance the tree by performing appropriate rotations on the subtree rooted with z. 
   There can be 4 possible cases that needs to be handled as x, y and z can be arranged 
   in 4 ways. Following are the possible 4 arrangements:

a) y is left child of z and x is left child of y (Left Left Case)
b) y is left child of z and x is right child of y (Left Right Case)
c) y is right child of z and x is right child of y (Right Right Case)
d) y is right child of z and x is left child of y (Right Left Case)

Following are the operations to be performed in above mentioned 4 cases. 
In all of the cases, we only need to re-balance the subtree rooted with z 
and the complete tree becomes balanced as the height of subtree (After appropriate rotations) 
rooted with z becomes same as it was before insertion. (See this video lecture for proof)

a) Left Left Case

T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
b) Left Right Case

     z                               z                           x
    / \                            /   \                        /  \
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
c) Right Right Case

  z                                y
 /  \                            /   \
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
d) Right Left Case

   z                            z                            x
  / \                          / \                          /  \
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4 
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

class TreeNode{
public:
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree{
private: 
    int height(TreeNode* n);
    int getBalance(TreeNode* n);
    int minValue(TreeNode* n);
    TreeNode* leftRotation(TreeNode* n);
    TreeNode* rightRotation(TreeNode* n);
public:
    TreeNode* insert(TreeNode* root, int key);
    TreeNode* remove(TreeNode* root, int key);

public:
    void inOrderTraversal(TreeNode* root, vector<int>& ans) {
        ans.clear();
        if (root == nullptr) return;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                ans.push_back(p->val);
                p = p->right;
            }
        }
    }
    vector<int> inOrderTraversal(TreeNode* root) {
        vector<int> ans;
        inOrderTraversal(root, ans);
        return ans;
    }
};

// 1. Insert a key into the AVL tree.
// 2. Return the new root after rebalance;
TreeNode* AVLTree::insert(TreeNode* root, int key) {
    if (root == nullptr)
        return new TreeNode(key);

    // Becasue root->left could be changed due to rebalance after insertion, 
    // we need to set root->left/right with return value;
    if (key < root->val)
        root->left = insert(root->left, key); 
    else if (key > root->val) 
        root->right = insert(root->right, key);
    else 
        return root; // duplicate key in BST is not allowed;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Case#a: Left Left Case
    if (balance > 1 && key < root->left->val) 
        return rightRotation(root);
    // case#c: Right Right Case
    if (balance < -1 && key > root->right->val)
        return leftRotation(root);
    // case#b: Left Right Case
    if (balance > 1 && key > root->left->val) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    // case#d: Right Left Case
    if (balance < -1 && key < root->right->val) {
        root->right = rightRotation(root->right);   
        return leftRotation(root);
    }
    
    // Return unchanged root if balance is OK
    return root;
}

// 1. Remove a node whose val equals to key
// 2. Return the new root after remove with re-balance. 
//    if the subTree is nullptr, root->left/right pointer will be updated to nullptr;
TreeNode* AVLTree::remove(TreeNode* root, int key) {
    if (root == nullptr) return nullptr;
    if (key < root->val)
        root->left = remove(root->left, key);
    else if (key > root->val)
        root->right = remove(root->right, key);
    else {
        // one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            TreeNode* tmp = root->left? root->left : root->right;
            if (tmp == nullptr) {
                // no child
                tmp = root;
                root = nullptr;  // <<< no need update parent pointer as we will return the new root as return value;
            } else 
                *root = *tmp;    // default copy constructor will just copy member bitwise
            delete tmp;
        } else {
            // with two children
            // Get min value in the right subTree, replace it with root node and delete it in right subTree.
            int minKey = minValue(root->right);
            root->val = minKey;
            root->right = remove(root->right, minKey);
        }
    }
    // if no node left, just return null;
    if (root == nullptr) return nullptr;
    // update height
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Left left case
    // Note: when getBalance(root->left) is 0, it works for both Left left case and Left right case.
    // But it would be much efficient to rotate just once so we merge it in Left left case.
    if (balance > 1 && getBalance(root->left) >= 0) { 
        return rightRotation(root);
    }
    // Left right case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    // Right right case
    // Same note as for when getBalance(root->right) is 0;
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotation(root);
    }
    // Right left case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

int AVLTree::minValue(TreeNode* n) {
    assert(n != nullptr);
    while (n->left) {
        n = n->left;
    }
    return n->val;
}

int AVLTree::getBalance(TreeNode* n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
}

int AVLTree::height(TreeNode* n) {
    if (n == nullptr) return 0;
    return n->height;
}

//
//   y                       x
//  / \    Left Rotate      / \
// T1  x   ===========>    y   T3
//    / \                 / \
//   T2  T3              T1  T2
//
TreeNode* AVLTree::leftRotation(TreeNode* n) {
    TreeNode* x = n->right;
    n->right = x->left;
    x->left = n;
    n->height = 1 + max(height(n->left), height(n->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

//   
//     y                           x
//    / \    Right Rotate         / \
//   x   T3  ============>       T1  y
//  / \                             / \
// T1  T2                          T2 T3
//
TreeNode* AVLTree::rightRotation(TreeNode* n) {
    TreeNode* x = n->left;
    n->left = x->right;
    x->right = n;
    n->height = 1 + max(height(n->left), height(n->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

int main() {
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    AVLTree avl;
    TreeNode* root = nullptr;
    for (auto x:v) root = avl.insert(root, x);
    
    vector<int> out = avl.inOrderTraversal(root);
    cout << "In-Order Traversal: ";
    for (auto x:out) cout << x << ", ";
    cout << endl;

    for (int i = 1; i <=4; i++)
        root = avl.remove(root, 2*i);
    
    out = avl.inOrderTraversal(root);
    cout << "In-Order Traversal: ";
    for (auto x:out) cout << x << ", ";
    cout << endl;

    return 0;
}
