/*
 * 101. Symmetric Tree
 *
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
 *
 * For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
 *
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * But the following [1,2,2,null,3,null,3] is not:
 *     1
 *    / \
 *   2   2
 *    \   \
 *     3   3
 * Note:
 * Bonus points if you could solve it both recursively and iteratively.
 * */

#include <iostream>
#include <deque>
#include <queue>
#include <climits>
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
    bool isSymmentric(deque<int>& dq) {
        while (!dq.empty()) {
            int a = dq.front();
            dq.pop_front();
            if (dq.empty())
                return true;
            int b = dq.back();
            dq.pop_back();
            if (a != b) 
                return false;
        }
        return true;
    }
    bool isSymmetric(TreeNode* root) {
        // level order traversal
        if (root == nullptr) return true;
        TreeNode* p;
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        deque<int> dq;
        while (!q.empty()) {
            p = q.front();
            q.pop();
            if (p) {
                dq.push_back(p->val);
                if (p->left) q.push(p->left);
                else if (p->val != INT_MAX) q.push(new TreeNode(INT_MAX));
                if (p->right) q.push(p->right);
                else if (p->val != INT_MAX) q.push(new TreeNode(INT_MAX));
            } else if (!q.empty()) {
                q.push(nullptr);
                if (!isSymmentric(dq))
                    return false;
                dq.clear();
            }
        }

        return isSymmentric(dq);
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(2);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(4);
    r->right->left = new TreeNode(4);
    r->right->right = new TreeNode(3);

    Solution s;
    cout << s.isSymmetric(r) << endl;

    r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(2);
    r->left->right = new TreeNode(3);
    r->right->right = new TreeNode(3);
    cout << s.isSymmetric(r) << endl;

    r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(2);
    r->left->left = new TreeNode(3);
    r->right->right = new TreeNode(3);
    cout << s.isSymmetric(r) << endl;

    r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(2);
    r->left->right= new TreeNode(3);
    r->right->left= new TreeNode(3);
    cout << s.isSymmetric(r) << endl;
    return 1;
}
