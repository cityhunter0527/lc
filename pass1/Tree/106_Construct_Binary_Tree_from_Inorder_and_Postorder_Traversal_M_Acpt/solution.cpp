/*
 * 106. Construct Binary Tree from Inorder and Postorder Traversal
 *
 * Given inorder and postorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree.
 * */

#include <iostream>
#include <vector>
using namespace std;
/** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


// TODO: Implemente an non-recursive way
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());                    
    }

private:
    template <typename Iterator>
    TreeNode *buildTree(Iterator inStart, Iterator inEnd, Iterator postStart, Iterator postEnd) {
        if (inStart == inEnd) return nullptr;
        if (postStart == postEnd) return nullptr;
        
        
        auto root = new TreeNode(*prev(postEnd));
        int i = 0;
        for (auto j = inStart; j < inEnd; j++, i++) {
            if (root->val == *j)
                break;
        }

        root->left = buildTree(inStart, inStart+i, postStart, postStart+i);
        root->right = buildTree(inStart+i+1, inEnd, postStart+i, prev(postEnd));
        return root;
    }
};

int main() {
    vector<int> inOrder = {1,2,3,4,5,6,7,8,9};
    vector<int> postOrder = {1,3,5,4,2,8,9,7,6};
    Solution s;
    TreeNode* root = s.buildTree(inOrder, postOrder);
    return 1;
}
