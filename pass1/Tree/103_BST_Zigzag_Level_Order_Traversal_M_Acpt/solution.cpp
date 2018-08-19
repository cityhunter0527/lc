/*
 * 103. Binary Tree Zigzag Level Order Traversal
 *
 * Given a binary tree, return the zigzag level order traversal of its nodes' values. 
 * (ie, from left to right, then right to left for the next level and alternate between).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * 
 * return its zigzag level order traversal as:
 *
 * [
 *  [3],
 *  [20,9],
 *  [15,7]
 * ]
 *
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
};

class Solution {
public:
    // level order traversal using queue
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> v;
        if (root == nullptr) return v;

        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        TreeNode* p = root;
        s1.push(p);
        while (!s1.empty()) {
            vector<int> l;
            while (!s1.empty()) {
                p = s1.top();
                s1.pop();
                // visit p
                l.push_back(p->val);
                if (p->left)
                    s2.push(p->left);
                if (p->right)
                    s2.push(p->right);
            }
            // Done wit current level.
            // Move to next level
            if (!l.empty())
                v.push_back(l);
            
            vector<int> l2;
            while (!s2.empty()) {
                p = s2.top();
                s2.pop();
                // visit p
                l2.push_back(p->val);
                if (p->right)
                    s1.push(p->right);
                if (p->left)
                    s1.push(p->left);
            }
            if (!l2.empty())
                v.push_back(l2);
        }

        return v;
    }
};

int main () {
    TreeNode* r = new TreeNode(12);
    r->left = new TreeNode(7);
    r->right = new TreeNode(18);
    r->left->left = new TreeNode(5);
    r->left->right = new TreeNode(9);
    r->left->left->left = new TreeNode(2);
    r->left->left->right = new TreeNode(6);
    r->left->right->left= new TreeNode(8);

    Solution s;
    vector<vector<int>> v = s.zigzagLevelOrder(r);
    for (auto x: v) {
        for (auto y: x) {
            cout<<y<<", ";
        }
        cout<<endl;
    }
    return 1; 
}
