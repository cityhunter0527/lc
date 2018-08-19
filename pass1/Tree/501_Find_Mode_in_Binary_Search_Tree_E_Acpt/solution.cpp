/*
 * 501. Find Mode in Binary Search Tree
 *
 * Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.
 *
 * Assume a BST is defined as follows:
 *
 * The left subtree of a node contains only nodes with keys less than or equal to the node's key.
 * The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
 * Both the left and right subtrees must also be binary search trees.
 * For example:
 * Given BST [1,null,2,2],
 *    1
 *     \
 *      2
 *     /
 *    2
 * return [2].
 *
 * Note: If a tree has more than one mode, you can return them in any order.
 *
 * Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
 * */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/** Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // in-order traversal
    // BST: in-order traversal is in increasing order
    void dfs(TreeNode* n, long long& curVal, int& maxCnt, int& curCnt, vector<int>& res) {
        if (n == nullptr) return;
        dfs(n->left, curVal, maxCnt, curCnt, res);
        // visit n
        if (n->val == curVal) 
            curCnt++;
        else {
            curVal = n->val;
            curCnt = 1;
        }
        if (curCnt > maxCnt) {
            maxCnt = curCnt;
            res.clear();
            res.push_back(curVal);
        } else if (curCnt == maxCnt) {
            res.push_back(curVal);
        }

        // if curCnt is smaller than maxCnt, do nothing.
       
        dfs(n->right, curVal, maxCnt, curCnt, res);
        return;
    }
    vector<int> findMode(TreeNode* root) {
        vector<int>  res;
        long long curVal = INT_MAX + 1LL; 
        int maxCnt = 0, curCnt = 0;
        dfs(root, curVal, maxCnt, curCnt, res);
        return res;
    }
};

int main() {
    TreeNode *r = new TreeNode(10);
    r->left = new TreeNode(6);
    r->left->left = new TreeNode(6);
    r->left->right = new TreeNode(8);
    r->right = new TreeNode(20);
    r->right->left = new TreeNode(20);
    Solution s;
    vector<int> out = s.findMode(r);

    for (auto x:out) {
        cout << x << ", " ;
    }
    cout << endl;
    return 1;
}
