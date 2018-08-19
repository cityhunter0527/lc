/*
 * 108. Convert Sorted Array to Binary Search Tree 
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 * */

/*** Definition for a binary tree node. **/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int val = nums[nums.size()/2];
        TreeNode* root = new TreeNode(val);
        auto pos = find(nums.begin(), nums.end(), val);
        root->left = sortedArrayToBST(nums.begin(), pos);
        root->right = sortedArrayToBST(next(pos), nums.end());
        return root;
    }
    template <typename Iterator>
    TreeNode* sortedArrayToBST(Iterator start, Iterator end) {
        if(start>=end) 
            return nullptr;
        auto size = distance(start, end);
        int val = *(start + size/2);
        auto pos = find(start, end, val);

        TreeNode* root = new TreeNode(val);
        root->left = sortedArrayToBST(start, pos);
        root->right = sortedArrayToBST(next(pos), end);
        return root;
    }

    vector<int> inOrder(TreeNode* root){
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                res.push_back(p->val);
                p = p->right;
            }
        }
        return res;
    }
};

int main () {
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    Solution s;
    TreeNode* root = s.sortedArrayToBST(v);
#if 1
    vector<int> out = s.inOrder(root);
    
    for (auto i : out)
        cout<<i;
#endif
    return 1;
}
