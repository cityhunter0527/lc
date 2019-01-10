/*
 * Given the root node of a binary search tree (BST) and a value. 
 * You need to find the node in the BST that the node's value equals the given value. 
 * Return the subtree rooted with that node. If such node doesn't exist, you should return NULL.

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3

And the value to search: 2
You should return this subtree:

      2     
     / \
    1   3
In the example above, if we want to search the value 5, since there is no node with value 5, we should return NULL.

Note that an empty tree is represented by NULL, therefore you would see the expected output (serialized tree format) as [], not null. 
 *
 * */

#include <iostream>
struct TreeNode {
	int val;
	TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (!root) return nullptr;
        if (root->val == val) return root;
        TreeNode* l = searchBST(root->left, val);
        if (l) 
            return l;
        else 
           return searchBST(root->right, val);
    }
};

int main() {
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(2);
    r->right = new TreeNode(7);

    r->left->left = new TreeNode(1);
    r->left->right = new TreeNode(3);
    
    Solution s;

    TreeNode* o = s.searchBST(r, 2);
    std::cout << o->val << std::endl;
    
    o = s.searchBST(r, 5);

    if (o)
        std::cout << "fail" << std::endl;
    else 
        std::cout << "pass" << std::endl;
        
    return 0;
}
