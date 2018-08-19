/*
 * Given a binary tree, imagine yourself standing on the right side of it, 
 * return the values of the nodes you can see ordered from top to bottom.
 *
 * For example:
 * Given the following binary tree,
 *    1            <---
 *  /   \
 * 2     3         <---
 *  \     \
 *   5     4       <---
 *  You should return [1, 3, 4].
 * */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
/** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // level order traversal
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        int prev;
        while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop();
            if (p == nullptr) {
                res.push_back(prev);
                if (!q.empty()) q.push(nullptr);
            } else {
                prev = p->val;
                if (p->left) 
                    q.push(p->left);
                if (p->right)
                    q.push(p->right);
            }
        
        }
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(2);
    r->right = new TreeNode(3);
    r->left->right = new TreeNode(5);
    r->right->right = new TreeNode(4);

    Solution s;
    vector<int> v = s.rightSideView(r);
    for (auto x:v) {
        cout << x << ",";   
    }
    cout << endl;
    return 1;
}
