/*
 * 108. Convert Sorted Array to Binary Search Tree
 *
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/** *  * Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
        TreeNode* root = nullptr;
        if (start > end) return root;
        int mid = start + (end-start)/2;
        root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, start, mid-1);
        root->right = sortedArrayToBST(nums, mid+1, end);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size()-1);
    }

    vector<int> inOrder(TreeNode* root) {
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

int main() {
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    Solution s;
    TreeNode* r = s.sortedArrayToBST(v);
    vector<int> out = s.inOrder(r);
    for (auto x:out)
        cout << x << ",";
    cout << endl;
    return 1;
}
