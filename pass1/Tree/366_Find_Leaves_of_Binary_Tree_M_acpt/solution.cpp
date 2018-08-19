/*
 * 366. Find Leaves of Binary Tree
 * Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.

Example:
Given binary tree 
          1
         / \
        2   3
       / \
      4   5    
Returns [4, 5, 3], [2], [1].

Explanation:
1. Removing the leaves [4, 5, 3] would result in this tree:

          1
         / 
        2          
2. Now removing the leaf [2] would result in this tree:

          1          
3. Now removing the leaf [1] would result in the empty tree:

          []         
Returns [4, 5, 3], [2], [1]. 
 *
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;
/*** Definition for a binary tree node. **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    // iterative:
    // postOrder:
    //     left child
    //     right child
    //     root
    // With postOrder iterative traversal with stack, 
    // we can always get parent of the node being visited in stack's top() (e.g. parent is always in the top after left/right child is poped).
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> res;
        vector<int> leaf;
        TreeNode* p = root, *visit, *parent = nullptr, *lastNodeVisited = nullptr;
        stack<TreeNode*> s;
        while (p) { // if root is not null
            while (!s.empty() || p) {
                if (p) {
                    s.push(p);
                    p = p->left;
                } else {
                    visit = s.top();
                    if (visit->right && visit->right != lastNodeVisited) {
                        p = visit->right;
                    } else {
                        s.pop();
                        // Visit node and only interested with leaf node
                        // Need to use 'parent' to exclude them since we change parent's left/child to nullptr if they are leaf node; 
                        if (!visit->left && !visit->right && visit != parent) {
                            leaf.push_back(visit->val);
                            if (!s.empty()) {
                                parent = s.top();
                                visit == parent->left ? (parent->left = nullptr) : (parent->right = nullptr);
                            } else {
                                root = nullptr; // We are done
                            }
                        }
                        lastNodeVisited = visit;
                    }
                }
            }
            res.push_back(leaf);
            leaf.clear();
            p = root;
            parent = nullptr;
            lastNodeVisited = nullptr;
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    Solution s;
    vector<vector<int>> res = s.findLeaves(root);

    for (auto x: res) {
        for (auto y: x) {
            cout << y << ", ";
        }
        cout << endl;
    }
    return 1;
}
