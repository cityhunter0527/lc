/*
 * 1008 Construct Binary Search Tree from Preorder Traversal
 * Return the root node of a binary search tree that matches the given preorder traversal.
 *
 *  Example 1:
 *          8
 *         / \
 *        5   10
 *       / \    \
 *      1   7   12  
 *
 *  Input: [8,5,1,7,10,12]
 *  Output: [8,5,10,1,7,null,12]
 *
 *   Note: 
 *
 *   1 <= preorder.length <= 100
 *   The values of preorder are distinct.
 * */
#include <iostream>
#include <vector>
#include <iterator>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* helper(std::vector<int>& v, std::vector<int>::iterator start, std::vector<int>::iterator end) {
        if (start < end) {
            auto k = *start;
            TreeNode* r = new TreeNode(k);
            auto l_start = std::next(start);
            auto r_start = std::lower_bound(l_start, end, k);
            auto l_end = r_start;
            r->left = helper(v, std::next(start), l_end);
            r->right = helper(v, r_start, end);
            return r;
        } else {
            return nullptr;
        }
    }

    TreeNode* bstFromPreorder(std::vector<int>& preorder) {
        if (preorder.size() == 0) {
            return nullptr;
        } 

        return helper(preorder, preorder.begin(), preorder.end());
    }

    // pre-order print
    void print(TreeNode* r) {
        if (r == nullptr) {
            return;
        }
        std::cout << r->val << ", ";
        print(r->left);
        print(r->right);
    }
};


int main() {
    std::vector<int> v = {8, 5, 1, 7, 10, 12};
    Solution s;
    TreeNode* r = s.bstFromPreorder(v);
    s.print(r);
    return 1;
}
