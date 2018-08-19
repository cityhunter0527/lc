/*
 * 236. Lowest Common Ancestor of a Binary Tree
 *  
 *  Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.  
 *  According to the definition of LCA on Wikipedia: 
 *      "The lowest common ancestor is defined between two nodes v and w as the lowest node 
 *      in T that has both v and w as descendants (where we allow a node to be a descendant of itself)."

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
    For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. 
    Another example is LCA of nodes 5 and 4 is 5, since a node can be a 
    descendant of itself according to the LCA definition.
 **/

#include <iostream>
#include <vector>
#include <stack>
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

#if 0
    // post-order traversal
    //      visit left
    //      visit right
    //      visit current
    //
    // iterative:
    //     When n is found, return all the node in stack, which is path from root to this node.
    vector<TreeNode*> getPath(TreeNode* root, TreeNode* n) {
        vector<TreeNode*> res;
        if (root == nullptr) return res;

        stack<TreeNode*> s;
        TreeNode* p = root, *lastp = nullptr;
        while (!s.empty() || p) {
            if (p == n) {
                break;
            }

            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                if (p->right && p->right != lastp) {
                    p = p->right;
                } else {
                    lastp = p;
                    s.pop();
                    p = nullptr;
                }
            }
        }

        res.push_back(p);
        while(!s.empty()) {
            p = s.top(); 
            s.pop();
            res.insert(res.begin(), p);
        }
        return res;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> p1  = getPath(root, p);
        vector<TreeNode*> p2  = getPath(root, q);
        
        // get commom Ancestor
        TreeNode* res = nullptr;
        for (int i = 0; i < p1.size(); i++) {
            if (p1[i] == p2[i]) {
                res = p1[i];
            } else 
                break;
        }
        return res;
    }
#endif
    // extend return value of lowestCommonAncestor:
    // nullptr: neither p nor q was found in this subTree;
    // not-null: p or q (or both) is found in this subTree.
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        if (l == nullptr)
            return r;
        if (r == nullptr)
            return l;
        return root;
    }
};

int main() {
    TreeNode* r = new TreeNode(3);
    r->left = new TreeNode(5);
    r->right = new TreeNode(1);
    r->left->left = new TreeNode(6);
    r->left->right = new TreeNode(2);
    r->left->right->left = new TreeNode(7);
    r->left->right->right = new TreeNode(4);
    r->right->left = new TreeNode(0);
    r->right->right = new TreeNode(8);

    Solution s;
    TreeNode* o = s.lowestCommonAncestor(r, r->left->left, r->left->right->right);
    cout << o->val;
    cout << endl;
    return 1;
}
