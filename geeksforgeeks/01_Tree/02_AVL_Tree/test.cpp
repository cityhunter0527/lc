#include <iostream>
#include <assert.h>
using namespace std;

class TreeNode {
public: 
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int minValue(TreeNode* n) {
        assert(n != nullptr);
        while (n->left) {
            n = n->left;
        }
        return n->val;
    }

    TreeNode* remove(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (key < root->val)
            root->left = remove(root->left, key);
        else if (key > root->val)
            root->right = remove(root->right, key);
        else {
            // one child or no child
            if (root->left == nullptr || root->right == nullptr) {
                TreeNode* tmp = root->left? root->left : root->right;
                if (tmp == nullptr) { // <<< no child
                    tmp = root;
                    root = nullptr; // <<< since root is going to be returned, the parent pointer will be set as null
                } else
                    *root = *tmp; // default copy constructor will just copy member bitwise
                delete tmp;
            } else {
                // Two children
                // Get min value in the right subTree, replace it with root node and delete it in right subTree.
                int minKey = minValue(root->right);
                root->val = minKey;
                root->right = remove(root->right, minKey);
            }
        }
        return root; 
    }
};

int main() {
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(2);
    r->right = new TreeNode(6);
    r->left->left = new TreeNode(1);
    r->left->right = new TreeNode(3);
    
    r->right->left = new TreeNode(5);
    r->right->right = new TreeNode(7);
    
    Solution s;
    TreeNode* root = s.remove(r, 3);

    return 0;
}
