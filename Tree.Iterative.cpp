/* 
 * Binary Tree Preorder Traversal
 * 
 * Iterative way (non-recursive)
 * */
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // Pre-Order:
    // * Vist curent node;
    // * Pre-Order left tree;
    // * Pre-Order right tree;
    vector<int> preOrderTraversal(TreeNode *root) {
         stack<TreeNode*> s;
         vector<int> r;
         TreeNode* p = root;
         if (p == NULL)
             return r;
         s.push(p);
         while (!s.empty()) {
             p = s.top();
             r.push_back(p->val);
             s.pop();
             if (p->right)
                 s.push(p->right);
             if (p->left)
                 s.push(p->left);
         }
         return r;
    }

    // In-Order:
    // * In-Order traversal left tree
    // * visit current node
    // * In-Order traversal right tree
    vector<int> inOrderTraversal(TreeNode *root) {
        stack<TreeNode*> s; 
        TreeNode *p = root;
        vector<int> r;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                r.push_back(p->val);
                s.pop();
                p = p->right;
            }
        }
        return r;
    }

    // post-Order
    // * post-Order traversal left tree
    // * post-Order traversal right tree
    // * visit current node
    vector<int> postOrderTraversal(TreeNode *root) {
        stack<TreeNode*> s;
        vector<int> r;
        TreeNode* p = root, *lastVisitedNode = NULL;
        while (!s.empty() || p) {
            if (p) {
                // Keep pushing p->left until no left child;
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                // Need distinguish whether we have visited the right child before.
                if (p->right && p->right != lastVisitedNode) {
                    // keep pushing p->right to stack and repeat post-Order traversal
                    p = p->right;
                } else {
                    // either p->right is NULL or we've already visited p->right.
                    // Then visit current node and store lastVisitedNode
                    lastVisitedNode = p;
                    r.push_back(p->val);
                    s.pop();
                    p = NULL;
                }
            }
        }
        return r;
    }

    vector<int> levelOrderTraversal(TreeNode* root) {
        vector<int> r;
        if (root == nullptr) return r;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* p = q.front();
            q.pop();
            r.push_back(p->val);
            if (p->left)
                q.push(p->left);
            if (p->right)
                q.push(p->right);
        }
        return r;
    }
};

int main() {
    return 1;
}
