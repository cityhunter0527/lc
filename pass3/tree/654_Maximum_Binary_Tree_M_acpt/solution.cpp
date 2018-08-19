/**
Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].
**/

#include <iostream>
#include <vector>
using namespace std;

/** * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private: 
    int getMaxId(vector<int>& nums, int l, int r) {
        int res = nums[l], id = l;
        while (++l <= r) { 
            if (res < nums[l]) {
                res = nums[l];
                id = l;
            }
        }
        return id;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums, int l, int r) {
        TreeNode* n = nullptr;
        if (l <= r) {
            int id = getMaxId(nums, l, r);       
            n = new TreeNode(nums[id]);
            n->left = constructMaximumBinaryTree(nums, l, id-1);
            n->right = constructMaximumBinaryTree(nums, id+1, r);
        } 

        return n;
    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return constructMaximumBinaryTree(nums, 0, nums.size()-1);
    }
};

int main() {
    vector<int> v = {3,2,1,6,0,5};
    Solution s;
    TreeNode* r = s.constructMaximumBinaryTree(v);

    return 1;
}
