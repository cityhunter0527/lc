/*
 Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
*/

#include <iostream>
#include <stack>
#include <unordered_map>
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
    // unordered map 
    // for each node in tree:
    //     if (m[n->val]) 
    //         return true;
    //     else 
    //         m[target - n->val] = true;
    //
    // return false;
    //
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        // in-order traversal;
        unordered_map<int, bool> m;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                // visit p
                if (m.find(p->val) != m.end()) 
                    return true;
                else 
                    m[k-p->val] = true;
                p = p->right;
            } 
        }
        return false;
    }
};

int main() {
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(3);
    r->right = new TreeNode(6);
    r->left->left = new TreeNode(2);
    r->left->right = new TreeNode(4);
    r->right->right = new TreeNode(7);
    Solution s;
    cout << s.findTarget(r, 9) << endl;
    cout << s.findTarget(r, 29) << endl;
    return 1;
}
