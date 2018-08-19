/*
 * 538. Convert BST to Greater Tree
 *
 * Given a Binary Search Tree (BST), convert it to a Greater Tree such that every 
 * key of the original BST is changed to the original key plus sum of all keys 
 * greater than the original key in BST.
 *
 * Example:
 *
 * Input: The root of a Binary Search Tree like this:
 *               5
 *             /   \
 *            2     13
 *
 *  Output: The root of a Greater Tree like this:
 *    18
 *  /    \
 * 20     13
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
    TreeNode* convertBST(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return root;
        stack<TreeNode*> s;
        TreeNode* p = root;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);   
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
                    *it += p->val;
                }
                res.push_back(p->val);   
                p = p->right;
            }
        }
        
        p = root;
        int i = 0;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);   
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                p->val = res[i++];
                p = p->right;
            }
        }
        return root;
    }
};
// 
//
//        5
//       /  \
//      3     10
//    / \     / \
//   1   4   8   20
int main() {
    TreeNode* r = new TreeNode(5);
    r->left = new TreeNode(2);
    r->right = new TreeNode(13);

    Solution s;
    s.convertBST(r);
    return 1;
}
