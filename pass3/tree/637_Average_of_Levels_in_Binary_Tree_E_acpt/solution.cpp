/*
   637. Average of Levels in Binary Tree
 * Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.
 * */

// level order traversal

#include <iostream>
#include <vector>
#include <deque>
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        if (!root) return res;
        deque<TreeNode*> q;
        q.push_back(root);
        q.push_back(nullptr);
        unsigned int numNodes = 0;
        double sum = 0;
        while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop_front();
            if (p == nullptr) { 
                if (!q.empty()) {
                    q.push_back(nullptr);
                }
                res.push_back(sum/numNodes);
                numNodes = 0;
                sum = 0;
                continue;
            }
            numNodes++;
            sum += p->val;
            if (p && p->left) q.push_back(p->left);
            if (p && p->right) q.push_back(p->right);
        }
        return res;
    }
};

int main() {
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(9);
    r->right = new TreeNode(20);
    r->right->left = new TreeNode(15);
    r->right->right = new TreeNode(7);
    
    Solution s;
    vector<double> o = s.averageOfLevels(r);
    
    for (auto x:o) {
        cout << x << ", ";
    }
    cout << endl;
    return 1;
}
