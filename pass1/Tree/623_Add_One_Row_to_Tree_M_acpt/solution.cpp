/*
 * 623. Add One Row to Tree
 *
 * Given the root of a binary tree, then value v and depth d, 
 * you need to add a row of nodes with value v at the given depth d. 
 * The root node is at depth 1.

The adding rule is: given a positive integer depth d, for each NOT null 
tree nodes N in depth d-1, create two tree nodes with value v as N's left 
subtree root and right subtree root. And N's original left subtree should 
be the left subtree of the new left subtree root, its original right subtree 
should be the right subtree of the new right subtree root. If depth d is 1 
that means there is no depth d-1 at all, then create a tree node with value 
v as the new root of the whole original tree, and the original tree is the 
new root's left subtree.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \
  1   1
 /     \
3       1
Note:
The given d is in range [1, maximum depth of the given tree + 1].
The given binary tree has at least one tree node.
 * */


#include <iostream>
#include <queue>
using namespace std;

/*** Definition for a binary tree node. ***/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode* newRoot = new TreeNode(v);
            newRoot->left = root;
            return newRoot;
        }

        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        int curDepth = 1;
        while (!q.empty() && curDepth < d) {
            TreeNode* p = q.front();
            q.pop();
            if (p) { 
                TreeNode* l = p->left, *r = p->right;
                if (l) q.push(l);
                if (r) q.push(r);
                if (curDepth == d-1) {
                    p->left = new TreeNode(v); 
                    p->left->left = l;
                    p->right = new TreeNode(v);
                    p->right->right = r;
                }
            } else if (!q.empty())  {
                // p is nullptr
                curDepth++;
                q.push(nullptr);
            } 
        }

        return root;
    }
};

int main() {
    TreeNode* r = new TreeNode(4);
    r->left = new TreeNode(2);
    r->left->left = new TreeNode(3);
    r->left->right = new TreeNode(1);
    Solution s;
    TreeNode* newr = s.addOneRow(r, 1, 3);
    return 1;
}
