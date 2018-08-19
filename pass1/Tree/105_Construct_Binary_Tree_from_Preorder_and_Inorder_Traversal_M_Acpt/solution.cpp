/*
 * 105. Construct Binary Tree from Preorder and Inorder Traversal
 * 
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree.
 * */

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


// TODO: Make it non-recursive way
class Solution {
public:
    // 
    // 1. Get 1st element in "preorder" which is root.
    // 2. Locate root in "inorder":
    //    - In "inorder",  get num of count from [first elment, root-1], [root+1, last element]. 
    //
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

    template <typename Iterator>
    TreeNode *buildTree(Iterator preStartIt, Iterator preEndIt, Iterator inStartIt, Iterator inEndIt) {
        if (preStartIt == preEndIt) return nullptr;
        if (inStartIt == inEndIt) return nullptr;
        
        auto root = new TreeNode(*preStartIt);
        int i = 0;
        for (Iterator j = inStartIt; j < inEndIt; j++, i++) {
            if (root->val == *j)
                break;
        }

        root->left = buildTree(preStartIt+1, preStartIt+i+1, inStartIt, inStartIt+i);
        root->right = buildTree(preStartIt+i+1, preEndIt, inStartIt+i+1, inEndIt);
        return root;
    }
};

int main () {
    vector<int> preorder = {6,2,1,4,3,5,7,9,8};
    vector<int> inorder = {1,2,3,4,5,6,7,8,9};
   
    Solution s;
    TreeNode* r = s.buildTree(preorder, inorder);

    return 1;
}
