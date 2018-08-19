/** Binary Tree Inorder Traversal
 *  Given a binary tree, return the inorder traversal of its nodes' values.
 *
 * For example:
 * Given binary tree [1,null,2,3],
 *    1
 *     \
 *     2
 *    /
 *   3
 *  return [1,3,2].
 *
 *  Note: Recursive solution is trivial, could you do it iteratively?
 *  */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x), left(NULL), right(NULL) {}
};

class solution {
public:
    vector<int> inOrderTraversal(TreeNode *root) {
        stack<TreeNode*> s = stack<TreeNode*>();
        TreeNode *p = root;
        vector<int> inOrderVec;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                inOrderVec.push_back(p->val);
                s.pop();
                p = p->right;
            }
        }
        return inOrderVec;
    }
};
int main() {
    return 1;
}
