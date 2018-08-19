/*
 * 404. Sum of Left Leaves
 *
 * Find the sum of all left leaves in a given binary tree.
 *
 * Example:
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *
 * There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
 * */


#include <iostream>
#include <stack>
using namespace std;

/** *  Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isLeafNode (TreeNode* p) {
        return (p->left == nullptr) && (p->right == nullptr);
    }
    int sumOfLeftLeaves(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* p = root;
        int sum = 0;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;   
            } else {
                // visit p
                p = s.top();
                s.pop();
                if (p->left && isLeafNode(p->left)) {
                    sum += p->left->val;
                }
                p = p->right;

            }
        }
        return sum;
    }
};

int main () {
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(9);
    r->right = new TreeNode(20);
    r->right->left = new TreeNode(15);
    r->right->right = new TreeNode(7);

    Solution s;
    int v = s.sumOfLeftLeaves(r);
    cout << v << endl;
    return 1;
}
