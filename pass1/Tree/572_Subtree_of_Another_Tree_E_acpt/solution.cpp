/*
 * 572. Subtree of Another Tree
 *
 * Given two non-empty binary trees s and t, check whether tree t has exactly the 
 * same structure and node values with a subtree of s. A subtree of s is a tree 
 * consists of a node in s and all of this node's descendants. 
 *
 * The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false. 
 * */


#include <iostream>
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
    bool isSameTree(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr && t2 == nullptr) return true;
        if (t1 && t2 && (t1->val == t2->val))
            return isSameTree(t1->left, t2->left) && isSameTree(t1->right, t2->right);
        
        return false;
    }
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (!t) return true;
        if (!s) return false;
        bool r = isSubtree(s->left, t) || isSubtree(s->right, t);
        if (s->val != t->val)
            return b;
        else
            return b || (isSameTree(s->left, t->left) && isSameTree(s->right, t->right)); 
    }
};

int main() {
    /*
Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
*/
    TreeNode* s = new TreeNode(3);
    s->left = new TreeNode(4);
    s->right = new TreeNode(5);
    s->left->left = new TreeNode(1);
    s->left->right = new TreeNode(2);

    TreeNode* t = new TreeNode(4);
    t->left = new TreeNode(1);
    t->right = new TreeNode(2);

    Solution ss;
    cout << ss.isSubtree(s, t) << endl;

    s->left->right->left = new TreeNode(0);
    cout << ss.isSubtree(s, t) << endl;
}
