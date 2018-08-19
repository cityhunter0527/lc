/*
 Given a binary search tree and the lowest and highest boundaries as L and R, 
 trim the tree so that all its elements lies in [L, R] (R >= L). 
 You might need to change the root of the tree, so the result should return 
 the new root of the trimmed binary search tree.

Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2

Output: 
    1
      \
       2
Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output: 
      3
     / 
   2   
  /
 1
 *
 * */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public: 
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (!root) return nullptr;
        if (root->val < L) return trimBST(root->right, L, R);
        else if (root->val == L) {
            root->left = nullptr;
            root->right = trimBST(root->right, L, R);
            return root;
        } else if (root->val < R) {
            root->left = trimBST(root->left, L, R);     
            root->right = trimBST(root->right, L, R);     
            return root;
        } else if (root->val == R) {
            root->right = nullptr;
            root->left = trimBST(root->left, L, R);
            return root;
        } else  { // root->val > R
            return trimBST(root->left, L, R);
        }
    }
};

int main() {
    TreeNode* r = new TreeNode(3);
    r->left =  new TreeNode(0);
    r->right = new TreeNode(4);
    r->left->right = new TreeNode(2);
    r->left->right->left = new TreeNode(1);
    Solution s;
    TreeNode* newR = s.trimBST(r, 1, 3);   
    return 1;
}
