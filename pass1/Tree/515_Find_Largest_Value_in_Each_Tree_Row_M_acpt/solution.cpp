/* 
 * You need to find the largest value in each row of a binary tree.
 *
 * Example:
 * Input: 
 *
 *           1
 *          / \
 *         3   2
 *        / \   \
 *       5   3   9 
 * Output: [1, 3, 9]
 * */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left; 
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // level order traversal
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root); q.push(nullptr);
        
        int tmpMax = INT_MIN;
        while (!q.empty()) { 
            TreeNode* p = q.front();
            q.pop();
            if (p != nullptr) {
                tmpMax = max(tmpMax, p->val);
                if (p->left) q.push(p->left);
                if (p->right) q.push(p->right);
            } else {
                // finish one row
                res.push_back(tmpMax);
                tmpMax = INT_MIN;
                // insert row separator
                if (!q.empty()) q.push(nullptr);
            }
        }
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(1);
    r->left = new TreeNode(3);
    r->right = new TreeNode(2);
    r->left->left = new TreeNode(5);
    r->left->right = new TreeNode(3);
    r->right->right = new TreeNode(9);

    Solution s;
    vector<int> out = s.largestValues(r);

    for (auto x:out) {
        cout << x << ", ";
    }
    cout << endl;
    return 1;
}
