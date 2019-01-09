#include <queue>
#include <deque>
#include <stack>
#include <iostream>

struct TreeNode {
    int         val;
    TreeNode   *left;
    TreeNode   *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<int> pre_order_traversal_iterative(TreeNode* root) {
        std::vector<int> res;
        if (root == nullptr) return res;
        std::stack<TreeNode*>  s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* p = s.top();
            s.pop();
            res.push_back(p->val);

            if(p->right) 
                s.push(p->right);
            if(p->left) 
                s.push(p->left);
        }
        return res;
    }
    
    std::vector<int> in_order_traversal_iterative(TreeNode* root) {
        std::vector<int> res;
        TreeNode *p = root;
        std::stack<TreeNode*>  s;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                s.pop();
                // visit this node;
                res.push_back(p);
                p = p->right;
            }
        }
        return res;
    }
    
    std::vector<int> post_order_traversal_iterative(TreeNode* root) {
        std::vector<int> res;
        TreeNode* p = root, last_visted_node = nullptr;
        std::stack<TreeNode*> s;
        while (!s.empty() || p) {
            if (p) {
                s.push(p);
                p = p->left;
            } else {
                p = s.top();
                // need to check whether we are traversing back from left child or right child;
                if (p->right && p->right != last_visted_node) {
                    // back from left child, keep stepping down with right child
                    p = p->right;
                } else  {
                    // back from right child, no other child to visit, so visit this node;
                    last_visted_node = p;
                    // visit this node
                    res.push_back(p->val);
                    s.pop();
                    p = nullptr;
                }
            }
        }
        return res;
    }

    std::vector<int> level_order_traversal_iterative(TreeNode* root) {
        std::vector<int> res;
        if (root == nullptr)  return res;
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* tmp = q.front();
            q.pop();
            res.push_back(tmp->val);
            if (tmp->left)
                q.push(tmp->left);
            if (tmp->right)
                q.push(tmp->right);
        }
        return res;
        
    }
};

int main() {
    return 1;
}
